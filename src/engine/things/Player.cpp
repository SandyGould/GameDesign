#include "Player.h"

#include "../events/PlayerDeathEvent.h"
#include "../tweens/TweenJuggler.h"

constexpr int DEAD_ZONE = 10000;

Player::Player() : AnimatedSprite("player", "./resources/assets/Animated_Sprites/Player/Player.png", "./resources/assets/Animated_Sprites/Player/Player.xml", "Idle") {
    this->type = "player";
    this->saveType = this->type;
    this->hasCollision = true;

    this->width = 110;
    this->height = 80;
    this->pivot = {this->width / 2, this->height / 2};
    this->setHitbox(0.32, 0.66, 0.15, 0.98);

    shield = std::make_shared<Shield>();
    this->addChild(shield);
    // Player hitboxes are a bit wonky, so offset y to make it visually centered
    shield->position.y = 5;
    shield->width = 10;
    shield->height = 70;
    // Again, wonky hitboxes, why is why we don't offset the x pivot and why y _is_ offset
    shield->pivot = {-this->width / 2, this->height / 2 - 5};
    shield->visible = false;
}

void Player::changeHealth(int amount) {
    if (health + amount < 100) {
        if (health + amount > 0) {
            health += amount;
        } else {
            health = 0;
            alive = false;
            EventDispatcher::getInstance().dispatchEvent(new Event(PlayerDeathEvent::PLAYER_DEATH_EVENT));
        }
    } else {
        health = 100;
    }

    if (amount < 0 && alive) {
        auto damage = std::make_unique<Tween>("damage_player", shared_from_this());
        damage->animate(TweenableParam::ALPHA, 255, 40, 0, 12);
        damage->animate(TweenableParam::ALPHA, 40, 255, 12, 24);
        TweenJuggler::getInstance().add(std::move(damage));
    }
}
void Player::changeStamina(int amount) {
    this->stamina = std::clamp(stamina + amount, 0, 1000);
}

void Player::toggleShieldVisible(bool vis) {
    shield->visible = vis;
}

void Player::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    if (!alive) {
        AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
        return;
    }

    if (Game::instance->paused) {
        return;
    }

    this->width = 110;
	this->height = 80;
    this->deltaX = 0.0;
    this->deltaY = 0.0;
    this->interacting = false;
    bool idle = true;

    if (this->slideDirection == SlideDirection::None && this->stamina >= 30) {
        // Are they sliding?
        if ((pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end() && checkDoubleTaps(SDL_SCANCODE_RIGHT)) ||
            (joystickState.xVal1 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            this->setHitbox(0.28, 0.72, 0.5, 0.98);
            this->play("Slide");
            this->slideDirection = SlideDirection::Right;
            this->slideFrames = 60;
            this->changeStamina(-30);
        } else if ((pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end() && checkDoubleTaps(SDL_SCANCODE_LEFT)) ||
                   (joystickState.xVal1 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            this->setHitbox(0.28, 0.72, 0.5, 0.98);
            this->play("SlideLeft");
            this->slideDirection = SlideDirection::Left;
            this->slideFrames = 60;
            this->changeStamina(-30);
        } else if ((pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end() && checkDoubleTaps(SDL_SCANCODE_DOWN)) ||
                   (joystickState.yVal1 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            this->setHitbox(0.28, 0.72, 0.5, 0.98);
            this->play("Slide");
            this->slideDirection = SlideDirection::Down;
            this->slideFrames = 60;
            this->changeStamina(-30);
        } else if ((pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() && checkDoubleTaps(SDL_SCANCODE_UP)) ||
                   (joystickState.yVal1 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            this->setHitbox(0.28, 0.72, 0.5, 0.98);
            this->play("Slide");
            this->slideDirection = SlideDirection::Up;
            this->slideFrames = 60;
            this->changeStamina(-30);
        }
    }

    if (this->slideFrames != 0) {
        if (slideDirection == SlideDirection::Right) {
            this->deltaX = this->speed * 2;
        } else if (slideDirection == SlideDirection::Left) {
            this->deltaX = -this->speed * 2;
        } else if (slideDirection == SlideDirection::Up) {
            this->deltaY = -this->speed * 2;
        } else if (slideDirection == SlideDirection::Down) {
            this->deltaY = this->speed * 2;
        }

        this->slideFrames--;
        if (this->slideFrames == 0) {
            this->slideDirection = SlideDirection::None;
        }
    } else {
        if (this->stamina >= 3) {
            if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end() || joystickState.xVal1 - DEAD_ZONE > 0) {
                if (this->current.animName != "Run") {
                    this->setHitbox(0.46, 0.72, 0.23, 0.98);
                    this->play("Run");
                }
                this->deltaX += this->speed;
                this->changeStamina(-3);
                idle = false;
            }
            if ((pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) || joystickState.xVal1 + DEAD_ZONE < 0) {
                if (this->current.animName != "RunLeft") {
                    this->setHitbox(0.3, 0.56, 0.23, 0.98);
                    this->play("RunLeft");
                }
                this->deltaX -= this->speed;
                this->changeStamina(-3);
                idle = false;
            }
            if ((pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) || joystickState.yVal1 - DEAD_ZONE > 0) {
                if (this->current.animName != "Run") {
                    this->setHitbox(0.46, 0.72, 0.23, 0.98);
                    this->play("Run");
                }
                this->deltaY += this->speed;
                this->changeStamina(-3);
                idle = false;
            }
            if ((pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) || joystickState.yVal1 + DEAD_ZONE < 0) {
                if (this->current.animName != "Run") {
                    this->setHitbox(0.46, 0.72, 0.23, 0.98);
                    this->play("Run");
                }
                this->deltaY -= this->speed;
                this->changeStamina(-3);
                idle = false;
            }
        }

        if (idle) {
            if (this->current.animName != "Idle") {
                this->setHitbox(0.32, 0.66, 0.15, 0.98);
                this->play("Idle");
            }
        }

        // SHIELD CONTROLS
        if (shield->bashCooldown == 0) {
            if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end() && shield->switchCooldown == 0) {
                shield->switchType();
            }

            // Despite rotation being in radians, it rotates CW instead of CCW...
            if (this->stamina >= 2 && pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
                shield->rotation -= PI / 30;
                this->changeStamina(-2);
            }
            if (this->stamina >= 2 && pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
                shield->rotation += PI / 30;
                this->changeStamina(-2);
            }
            shield->rotation = std::fmod(shield->rotation, 2 * PI);

            if (this->stamina >= 70 &&
                pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.cend()) {
                shield->bash();
                this->changeStamina(-70);
            }

            // if (this->stamina >= 2) {
            //     if ((pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end() &&
            //          prevKeys.find(SDL_SCANCODE_D) == prevKeys.end()) ||
            //         joystickState.xVal2 - DEAD_ZONE > 0) {
            //         shield->rotation = std::remainder(shield->rotation, PI / 2);
            //         this->changeStamina(-2);
            //         if (this->stamina >= 70 &&
            //             (checkDoubleTaps(SDL_SCANCODE_D) ||
            //              (joystickState.xVal2 - DEAD_ZONE > 0 &&
            //               pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end()))) {
            //             shield->bash();
            //             this->changeStamina(-70);
            //         }
            //     }
            //     if ((pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end() &&
            //          prevKeys.find(SDL_SCANCODE_A) == prevKeys.end()) ||
            //         joystickState.xVal2 + DEAD_ZONE < 0) {
            //         shield->rotation = std::remainder(shield->rotation, PI / 2) + PI;
            //         this->changeStamina(-2);
            //         if (this->stamina >= 70 &&
            //             (checkDoubleTaps(SDL_SCANCODE_A) ||
            //              (joystickState.xVal2 + DEAD_ZONE < 0 &&
            //               pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end()))) {
            //             shield->bash();
            //             this->changeStamina(-70);
            //         }
            //     }
            //     if ((pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end() &&
            //          prevKeys.find(SDL_SCANCODE_S) == prevKeys.end()) ||
            //         joystickState.yVal2 - DEAD_ZONE > 0) {
            //         shield->rotation = std::remainder(shield->rotation, PI / 2) + PI / 2;
            //         this->changeStamina(-2);
            //         if (this->stamina >= 70 &&
            //             (checkDoubleTaps(SDL_SCANCODE_S) ||
            //              (joystickState.yVal2 - DEAD_ZONE > 0 &&
            //               pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end()))) {
            //             shield->bash();
            //             this->changeStamina(-70);
            //         }
            //     }
            //     if ((pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end() &&
            //          prevKeys.find(SDL_SCANCODE_W) == prevKeys.end()) ||
            //         joystickState.yVal2 + DEAD_ZONE < 0) {
            //         shield->rotation = std::remainder(shield->rotation, PI / 2) + 3 * PI / 2;
            //         this->changeStamina(-2);
            //         if (this->stamina >= 70 &&
            //             (checkDoubleTaps(SDL_SCANCODE_W) ||
            //              (joystickState.yVal2 + DEAD_ZONE < 0 &&
            //               pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end()))) {
            //             shield->bash();
            //             this->changeStamina(-70);
            //         }
            //     }
            // }
        }

        if (!shield->bashing &&
            pressedKeys.find(SDL_SCANCODE_SPACE) != pressedKeys.cend() &&
            prevKeys.find(SDL_SCANCODE_SPACE) == prevKeys.cend()) {
            this->interacting = true;
        }

        // STAMINA REFRESH
        this->changeStamina(5);
    }

    // Need to account for decimals
    this->storedDeltaX += deltaX;
    this->storedDeltaY += deltaY;

    // Round towards zero (truncate)
    this->position.x += static_cast<int>(storedDeltaX);
    this->storedDeltaX -= static_cast<int>(storedDeltaX);

    this->position.y += static_cast<int>(storedDeltaY);
    this->storedDeltaY -= static_cast<int>(storedDeltaY);

    updateHistory(pressedKeys);

    prevKeys = pressedKeys;

    // Reset speed
    this->speed = 4.0;

    AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
}

void Player::updateHistory(std::unordered_set<SDL_Scancode> pressedKeys) {
	for (int i = 0; i < history.size() - 1; i++) {
		history[i] = history[i + 1];
	}
	history[history.size() - 1] = pressedKeys;
}

bool Player::checkDoubleTaps(SDL_Scancode key) {
	for (int i = history.size() - 1; i >= 1; i--) {
		if (history[i].find(key) == history[i].end()) {
			for (int k = i - 1; k >= 0; k--) {
				if (history[k].find(key) != history[k].end()) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Player::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    if(other->type == "mage_attack"){
        this->changeHealth(-10);
        other->removeThis();
        return true;
    }
    if(other->type == "arrow"){
        other->removeThis();
        this->changeHealth(-10);
        return true;
    }
    if(other->type == "rubber_cannonball" || other->type == "cannonball"){
        this->cannonBallHit(other);
        this->changeHealth(-20);
        return true;
    }
    if(other->type == "poison_bomb"){
        this->changeHealth(-1);
        return true;
    }
    if(other->id == "shield_power_up"){
        this->toggleShieldVisible(true);
        return true;
    }
    if(other->type == "EnvironmentObject"){
        // TODO: Need to deal with changing hitboxes
        this->slideDirection = SlideDirection::None;
        this->slideFrames = 0;
    }
    return false;
}

void Player::cannonBallHit(std::shared_ptr<DisplayObject> other){
    //move the player back.
    other->removeThis();
}

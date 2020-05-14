#include "Player.h"

#include "../enemies/MageAttack.h"
#include "../events/PlayerDeathEvent.h"

#include <iostream>

#define HISTORY_SIZE 8
#define BASH_COOLDOWN 40
#define TOGGLE_COOLDOWN 40

using namespace std;

Player::Player() : AnimatedSprite("player", "./resources/assets/Animated_Sprites/Player/Player.png", "./resources/assets/Animated_Sprites/Player/Player.xml", "Idle") {
    type = "player";
    this->saveType = this->type;
    hasCollision = true;
    this->setHitbox(0.32, 0.66, 0.15, 0.98);

    history = new std::unordered_set<SDL_Scancode> [HISTORY_SIZE];
    shieldSwitchCooldown = 0;
    shieldBashCooldown = 0;

    shield = std::make_shared<Shield>();
    this->addChild(shield);
    shield->position.x = 105;
    shield->position.y = 10;
    shield->width = 10;
    shield->height = 70;
    shield->pivot = {50, 50};
    shield->visible = false;
}

void Player::changeHealth(int amount) {
    if (health + amount < 100) {
        if (health + amount > 0){
            health += amount;
        }
        else {
            health = 0;
            alive = false;
            EventDispatcher::getInstance().dispatchEvent(new Event(PlayerDeathEvent::PLAYER_DEATH_EVENT));
        }
    } else {
        health = 100;
    }
    if (amount < 0) {
        damage = std::make_shared<Tween>(shared_from_this());
        damage->animate(TweenableParams::ALPHA, 255, 40, 48);
        damage->animate(TweenableParams::ALPHA, 40, 200, 32);
        damage->animate(TweenableParams::ALPHA, 200, 40, 32);
        damage->animate(TweenableParams::ALPHA, 40, 255, 48);
        TweenJuggler::getInstance().add(damage);
    }
}
void Player::changeStamina(int amount) {
    if (stamina + amount < 1000) {
        if (stamina + amount > 0){
            stamina += amount;
        }
        else {
            stamina = 0;
        }
    } else {
        stamina = 1000;
    }
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

    // CHARACTER MOVEMENT
    this->width = 110;
	this->height = 80;
    bool idle = true;
    int DEAD_ZONE = 10000;
	if ((pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) || joystickState.xVal1 - DEAD_ZONE > 0) {
		if (checkDoubleTaps(SDL_SCANCODE_RIGHT) || (joystickState.xVal1 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            if (this->current.animName.compare("Slide") != 0){
                this->setHitbox(0.28, 0.72, 0.5, 0.98);
                this->play("Slide");
                this->slidin = true;
            }
			this->position.x += this->speed*2;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current.animName.compare("Run") != 0){
                this->setHitbox(0.46, 0.72, 0.23, 0.98);
                this->play("Run");
                this->slidin = false;
            }
			this->position.x += this->speed;
			this->changeStamina(-3);
		}
        idle = false;
	}
    if ((pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) || joystickState.xVal1 + DEAD_ZONE < 0) {
		if (checkDoubleTaps(SDL_SCANCODE_LEFT) || (joystickState.xVal1 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            if (this->current.animName.compare("SlideLeft") != 0){
                this->setHitbox(0.28, 0.72, 0.5, 0.98);
                this->play("SlideLeft");
                this->slidin = true;
            }
			this->position.x -= this->speed*2;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current.animName.compare("RunLeft") != 0){
                this->setHitbox(0.3, 0.56, 0.23, 0.98);
                this->play("RunLeft");
                this->slidin = false;
            }
			this->position.x -= this->speed;
			this->changeStamina(-3);
		}
        idle = false;
	}
	if ((pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) || joystickState.yVal1 - DEAD_ZONE > 0) {
		if (checkDoubleTaps(SDL_SCANCODE_DOWN) || (joystickState.yVal1 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            if (this->current.animName.compare("Slide") != 0){
                this->setHitbox(0.28, 0.72, 0.5, 0.98);
                this->play("Slide");
                this->slidin = true;
            }
			this->position.y += this->speed*2;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current.animName.compare("Run") != 0){
                this->setHitbox(0.46, 0.72, 0.23, 0.98);
                this->play("Run");
                this->slidin = false;
            }
			this->position.y += this->speed;
			this->changeStamina(-3);
		}
        idle = false;
	}
	if ((pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) || joystickState.yVal1 + DEAD_ZONE < 0) {
		if (checkDoubleTaps(SDL_SCANCODE_UP) || (joystickState.yVal1 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_LEFTSTICK) != pressedButtons.end())) {
            if (this->current.animName.compare("Slide") != 0){
                this->setHitbox(0.28, 0.72, 0.5, 0.98);
                this->play("Slide");
                this->slidin = true;
            }
			this->position.y -= this->speed*2;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current.animName.compare("Run") != 0){
                this->setHitbox(0.46, 0.72, 0.23, 0.98);
                this->play("Run");
                this->slidin = false;
            }
			this->position.y -= this->speed;
			this->changeStamina(-3);
		}
        idle = false;
	}

    if (idle) {
        if (this->current.animName.compare("Idle") != 0){
            this->setHitbox(0.32, 0.66, 0.15, 0.98);
            this->play("Idle");
            this->slidin = false;
        }
    }

	// SHIELD CONTROLS
    if (shieldBashCooldown == 0) {
        if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && shieldSwitchCooldown == 0) {
            shieldSwitchCooldown = TOGGLE_COOLDOWN;
    		shield->switchType();
    	}
    	if ((pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) || joystickState.xVal2 - DEAD_ZONE > 0) {
            shield->position.x = 105;
            shield->position.y = 10;
            shield->rotation = 0;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_D) || (joystickState.xVal2 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end())) {
                shield->bashing = true;
                shield->bashFrames =10;
                shieldBashCooldown = BASH_COOLDOWN;
    			shieldBash = std::make_shared<Tween>(shield);
                shieldBash->animate(TweenableParams::X, 105.0, 140.0, 10);
                shieldBash->animate(TweenableParams::X, 140.0, 105.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
    			this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if ((pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) || joystickState.xVal2 + DEAD_ZONE < 0) {
            shield->position.x = -5;
            shield->position.y = 10;
            shield->rotation = 0;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_A) || (joystickState.xVal2 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end())) {
                shieldBashCooldown = BASH_COOLDOWN;
                shield->bashing = true;
                shield->bashFrames = 10;
    			shieldBash = std::make_shared<Tween>(shield);
                shieldBash->animate(TweenableParams::X, -5.0, -40.0, 10);
                shieldBash->animate(TweenableParams::X, -40.0, -5.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
    			this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if ((pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) || joystickState.yVal2 - DEAD_ZONE > 0) {
            shield->position.x = -8;
            shield->position.y = 100;
            shield->rotation = PI / 2;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_S) || (joystickState.yVal2 - DEAD_ZONE > 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end())) {
                shieldBashCooldown = BASH_COOLDOWN;
                shield->bashing = true;
                shield->bashFrames =10;
    			shieldBash = std::make_shared<Tween>(shield);
                shieldBash->animate(TweenableParams::Y, 100.0, 135.0, 10);
                shieldBash->animate(TweenableParams::Y, 135.0, 100.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
                this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if ((pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) || joystickState.yVal2 + DEAD_ZONE < 0) {
            shield->position.x = 20;
            shield->position.y = -105;
            shield->rotation = -PI / 2;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_W) || (joystickState.yVal2 + DEAD_ZONE < 0 && pressedButtons.find(SDL_CONTROLLER_BUTTON_RIGHTSTICK) != pressedButtons.end())) {
                shieldBashCooldown = BASH_COOLDOWN;
                shield->bashFrames =10;
                shield->bashing = true;
    			shieldBash = std::make_shared<Tween>(shield);
                shieldBash->animate(TweenableParams::Y, -105.0, -140.0, 10);
                shieldBash->animate(TweenableParams::Y, -140.0, -105.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
    			this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    }

	// STAMINA REFRESH
	this->changeStamina(5);

    //COOLDOWN TICKS
    if (shieldSwitchCooldown > 0) {
        shieldSwitchCooldown--;
    }
    if (shieldBashCooldown > 0) {
        shieldBashCooldown--;
    }

    updateHistory(pressedKeys);

    AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
}

void Player::draw(AffineTransform& at) {
    AnimatedSprite::draw(at);
}

void Player::updateHistory(std::unordered_set<SDL_Scancode> pressedKeys) {
	for (int i = 0; i < HISTORY_SIZE-1; i++) {
		history[i] = history[i+1];
	}
	history[HISTORY_SIZE-1] = pressedKeys;
}

bool Player::checkDoubleTaps(SDL_Scancode key) {
	for (int i = HISTORY_SIZE-1; i >= 1; i--) {
		if (history[i].find(key) == history[i].end()) {
			for (int k = i-1; k >= 0; k--) {
				if (history[k].find(key) != history[k].end()) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Player::onCollision(std::shared_ptr<DisplayObject> other){
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
    return false;
}

void Player::cannonBallHit(std::shared_ptr<DisplayObject> other){
    //move the player back.
    other->removeThis();
}

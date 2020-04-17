#include "Player.h"
#include <iostream>
#include "../enemies/MageAttack.h"

#define HISTORY_SIZE 8
#define BASH_COOLDOWN 40
#define TOGGLE_COOLDOWN 40

Player::Player() : AnimatedSprite("player", "./resources/assets/Animated_Sprites/Player/Player.png", "./resources/assets/Animated_Sprites/Player/Player.xml") {
    type = "player";
    hasCollision = true;

    history = new std::unordered_set<SDL_Scancode> [HISTORY_SIZE];
    shieldSwitchCooldown = 0;
    shieldBashCooldown = 0;

    shield = new Shield();
	this->addChild(shield);
	shield->position.x = 105;
	shield->position.y = 10;
	shield->width = this->width * 20 / 110;
	shield->height = this->height;
	shield->pivot = {50, 50};
    shield->visible = false;
}

void Player::changeHealth(int amount) {
    if (health + amount < 100) {
        health += amount;
    } else {
        health = 100;
    }
}
void Player::changeStamina(int amount) {
    if (stamina + amount < 1000) {
        stamina += amount;
    } else {
        stamina = 1000;
    }
}

void Player::toggleShieldHidden() {
    shield->visible = !shield->visible;
}

void Player::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    // CHARACTER MOVEMENT
    bool idle = true;
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_RIGHT)) {
            if (this->current->animName.compare("Slide") != 0)
                this->play("Slide");
			this->position.x += 8;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current->animName.compare("Run") != 0)
                this->play("Run");
			this->position.x += 4;
			this->changeStamina(-3);
		}
        idle = false;
	}
    if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_LEFT)) {
            if (this->current->animName.compare("SlideLeft") != 0)
                this->play("SlideLeft");
			this->position.x -= 8;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current->animName.compare("RunLeft") != 0)
                this->play("RunLeft");
			this->position.x -= 4;
			this->changeStamina(-3);
		}
        idle = false;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_DOWN)) {
            if (this->current->animName.compare("Slide") != 0)
                this->play("Slide");
			this->position.y += 8;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current->animName.compare("Run") != 0)
                this->play("Run");
			this->position.y += 4;
			this->changeStamina(-3);
		}
        idle = false;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (checkDoubleTaps(SDL_SCANCODE_UP)) {
            if (this->current->animName.compare("Slide") != 0)
                this->play("Slide");
			this->position.y -= 8;
			this->changeStamina(-30);
            AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
            return;
		} else {
            if (this->current->animName.compare("Run") != 0)
                this->play("Run");
			this->position.y -= 4;
			this->changeStamina(-3);
		}
        idle = false;
	}

    if (idle) {
        if (this->current->animName.compare("Idle") != 0)
            this->play("Idle");
    }

	// SHIELD CONTROLS
    if (shieldBashCooldown == 0) {
        if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end() && shieldSwitchCooldown == 0) {
            shieldSwitchCooldown = TOGGLE_COOLDOWN;
    		shield->switchType();
    	}
    	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
            shield->bashing =
            shield->position.x = 105;
            shield->position.y = 10;
            shield->rotation = 0;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_D)) {
                shield->bashing = true;
                shield->bashFrames =10;
                shieldBashCooldown = BASH_COOLDOWN;
    			shieldBash = new Tween(shield);
                shieldBash->animate(TweenableParams::X, 105.0, 140.0, 10);
                shieldBash->animate(TweenableParams::X, 140.0, 105.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
    			this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
            shield->position.x = -20;
            shield->position.y = 10;
            shield->rotation = 0;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_A)) {
                shieldBashCooldown = BASH_COOLDOWN;            
                shield->bashing = true;
                shield->bashFrames = 10;
    			shieldBash = new Tween(shield);
                shieldBash->animate(TweenableParams::X, -20.0, -55.0, 10);
                shieldBash->animate(TweenableParams::X, -55.0, -20, 18);
                TweenJuggler::getInstance().add(shieldBash);
    			this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
            shield->position.x = -5;
            shield->position.y = 105;
            shield->rotation = PI / 2;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_S)) {
                shieldBashCooldown = BASH_COOLDOWN;
                shield->bashing = true;
                shield->bashFrames =10;
    			shieldBash = new Tween(shield);
                shieldBash->animate(TweenableParams::Y, 105.0, 140.0, 10);
                shieldBash->animate(TweenableParams::Y, 140.0, 105.0, 18);
                TweenJuggler::getInstance().add(shieldBash);
                this->changeStamina(-70);
                AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
                return;
    		}
    	}
    	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
            shield->position.x = 15;
            shield->position.y = -105;
            shield->rotation = -PI / 2;
            this->changeStamina(-2);
            if (checkDoubleTaps(SDL_SCANCODE_W)) {
                shieldBashCooldown = BASH_COOLDOWN;
                shield->bashFrames =10;
                shield->bashing = true;
    			shieldBash = new Tween(shield);
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

    TweenJuggler::getInstance().nextFrame();
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

bool Player::onCollision(DisplayObject* other){
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
    if(other->type == "knight"){
        this->changeHealth(-10);
        return true;
    }
    if(other->type == "poison_bomb"){
        this->changeHealth(-1);
        return true;
    }
    return false;
}

void Player::cannonBallHit(DisplayObject* other){
    //move the player back.
    other->removeThis();
}

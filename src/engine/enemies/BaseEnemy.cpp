#include "BaseEnemy.h"
#include <iostream>

BaseEnemy::BaseEnemy(std::string id, std::string spritesheet, std::string xml, std::string animName, std::shared_ptr<Player> player) : AnimatedSprite(id, spritesheet, xml, animName) {
    hasCollision=true;
    this->player = player;
    this->player->numOpponents += 1;
    this->type = "enemy";
}

void BaseEnemy::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if (Game::instance->paused) {
        return;
    }

    // Reset speed every tick
    this->speed = 1;
    AnimatedSprite::update(pressedKeys,joystickState,pressedButtons);
}

void BaseEnemy::changeHealth(int amount){
    this->health += amount;

    // Damage
    if (amount < 0) {
        auto damage = std::make_unique<Tween>("damage_" + this->id, shared_from_this());
        damage->animate(TweenableParams::ALPHA, 255, 40, 48);
        damage->animate(TweenableParams::ALPHA, 40, 200, 32);
        damage->animate(TweenableParams::ALPHA, 200, 40, 32);
        damage->animate(TweenableParams::ALPHA, 40, 255, 48);
        TweenJuggler::getInstance().add(std::move(damage));
    }
}

bool BaseEnemy::onCollision(std::shared_ptr<DisplayObject> other){
     if(other->type == "mage_attack" || other->type == "arrow") {
        if (std::static_pointer_cast<Projectile>(other)->reflected) {
            this->changeHealth(-50);
            other->removeThis();
        }
        return true;
    } if (other->id == "spike"){
        if(collisionWaitTime >= 10){
            this->changeHealth(-10);
            collisionWaitTime = 0;
        } else {
            collisionWaitTime++;
        }
    } else if (other->id.find("mud") != std::string::npos){
        this->speed = 0.5;
        return true;
    } else if (other->id.find("ice") != std::string::npos){
        this->speed = 2;
        return true;
    }
    if(other->type == "rubber_cannonball" || other->type == "cannonball"){
        this->changeHealth(-100);
        return true;
    }
    return false;
}

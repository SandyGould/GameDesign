#include "BaseEnemy.h"
#include <iostream>

BaseEnemy::BaseEnemy(std::string id, std::string spritesheet, std::string xml, std::string animName, std::shared_ptr<Player> player) : AnimatedSprite(id, spritesheet, xml, animName) {
    hasCollision=true;
    this->player = player;
    this->player->numOpponents += 1;
    this->type = "enemy";
}

void BaseEnemy::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    AnimatedSprite::update(pressedKeys,joystickState,pressedButtons);
}

void  BaseEnemy::draw(AffineTransform& at){
    AnimatedSprite::draw(at);
}

void BaseEnemy::changeHealth(int amount){
    this->health+=amount;
}

bool BaseEnemy::onCollision(std::shared_ptr<DisplayObject> other){
     if(other->type == "mage_attack" || other->type == "arrow") {
        if (std::static_pointer_cast<Projectile>(other)->reflected == true) {
            damage = std::make_shared<Tween>(shared_from_this());
            damage->animate(TweenableParams::ALPHA, 255, 40, 48);
            damage->animate(TweenableParams::ALPHA, 40, 200, 32);
            damage->animate(TweenableParams::ALPHA, 200, 40, 32);
            damage->animate(TweenableParams::ALPHA, 40, 255, 48);
            TweenJuggler::getInstance().add(damage);
            this->changeHealth(-20);
            other->removeThis();
        }
        return true;
    } if (other->type == "WalkOnObject" && other->id == "spike"){
        damage = std::make_shared<Tween>(shared_from_this());
        damage->animate(TweenableParams::ALPHA, 255, 40, 48);
        damage->animate(TweenableParams::ALPHA, 40, 200, 32);
        damage->animate(TweenableParams::ALPHA, 200, 40, 32);
        damage->animate(TweenableParams::ALPHA, 40, 255, 48);
        TweenJuggler::getInstance().add(damage);
        this->changeHealth(-20);
    }
    if(other->type == "rubber_cannonball" || other->type == "cannonball"){
        this->changeHealth(-100);
        return true;
    }
    return false;
}

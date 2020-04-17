#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(std::string id, std::string spritesheet, std::string xml, Player* player) : AnimatedSprite(id, spritesheet, xml){
    hasCollision=true;
    this->player = player;
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

//void BaseEnemy::onCollision(DisplayObject* other)

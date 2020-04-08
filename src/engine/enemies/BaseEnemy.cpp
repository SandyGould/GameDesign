#include "BaseEnemy.h"


BaseEnemy::BaseEnemy(std::string id, std::string filepath) : Sprite(id, filepath, Game::renderer){
    hasCollision=true;
}

void BaseEnemy::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    Sprite::update(pressedKeys,joystickState,pressedButtons);
}

void  BaseEnemy::draw(AffineTransform& at){
    Sprite::draw(at);
}

//void BaseEnemy::onCollision(DisplayObject* other)
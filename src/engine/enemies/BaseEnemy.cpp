#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(std::string id) : AnimatedSprite(id, Game::renderer){
    hasCollision=true;
}

void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    //AnimatedSprite::update(pressedKeys,joystickState,pressedButtons);
}

void draw(AffineTransform& at){
    //AnimatedSprite::draw(at);
}
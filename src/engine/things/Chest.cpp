#include "Chest.h"

Chest::Chest() : AnimatedSprite("chest", "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml") {
    hasCollision = true;
    this->type = "chest";
    this->play("ChestIdle");
}

void Chest::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    AnimatedSprite::update(pressedKeys,joystickState,pressedButtons);
}

void  Chest::draw(AffineTransform& at){
    AnimatedSprite::draw(at);
}

bool Chest::onCollision(std::shared_ptr<DisplayObject> other){
    return false;
}

#include "MageAttack.h"
#include "../events/EventDispatcher.h"

MageAttack::MageAttack() : Sprite("mageAttack", "./resources/assets/Animated_Sprites/Enemies/Mage/mageAttack.png") {
    hasCollision = true;
    this->width = this->height = 30;
}

void MageAttack::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void MageAttack::draw(AffineTransform& at) {
    Sprite::draw(at);
}

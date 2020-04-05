#include "Shield.h"
#include "../events/EventDispatcher.h"

Shield::Shield() : Sprite("shield", "./resources/character/Idle_1.png") {
    hasCollision = true;
}

void Shield::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Shield::draw(AffineTransform& at) {
    Sprite::draw(at);
}

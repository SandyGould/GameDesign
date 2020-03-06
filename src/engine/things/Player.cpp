#include "Player.h"
#include "../events/EventDispatcher.h"

Player::Player() : Sprite("player", "./resources/character/Idle_1.png") {
    hasCollision = true;
}

void Player::update(std::set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Player::draw(AffineTransform& at) {
    Sprite::draw(at);
}

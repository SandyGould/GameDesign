#include "Player.h"

Player::Player() : AnimatedSprite("player", "./resources/Spritesheets/test.png", "./resources/Spritesheets/test.xml"){//Sprite("player", "./resources/character/Idle_1.png") {
    hasCollision = true;
}



void Player::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
}

void Player::draw(AffineTransform& at) {
    AnimatedSprite::draw(at);
}

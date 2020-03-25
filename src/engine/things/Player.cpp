#include "Player.h"
#include "../events/EventDispatcher.h"

Player::Player() : AnimatedSprite("player", "./resources/Spritesheets/test.png", "./resources/Spritesheets/test.xml"){//Sprite("player", "./resources/character/Idle_1.png") {
    hasCollision = true;
}

void Player::update(std::set<SDL_Scancode> pressedKeys) {
    AnimatedSprite::update(pressedKeys);
}

void Player::draw(AffineTransform& at) {
    AnimatedSprite::draw(at);
}

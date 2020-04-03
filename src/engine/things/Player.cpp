#include "Player.h"
#include "../events/EventDispatcher.h"
#include <iostream>

using namespace std;

Player::Player() : AnimatedSprite("player", "./resources/assets/Spritesheets/Girl/Girl.png", "./resources/assets/Spritesheets/Girl.xml"){//Sprite("player", "./resources/character/Idle_1.png") {
    type = "player";
    hasCollision = true;
    health = 100;
    stamina = 1000;
}

void Player::changeHealth(int amount) {
    if (health + amount <= 100) {
        health += amount;
    } else {
        health = 100;
    }
}

void Player::changeStamina(int amount) {
    if (stamina + amount <= 1000) {
        stamina += amount;
    } else {
        stamina = 1000;
    }
}



void Player::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    AnimatedSprite::update(pressedKeys, joystickState, pressedButtons);
}

void Player::draw(AffineTransform& at) {
    AnimatedSprite::draw(at);
}

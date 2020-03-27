#include "Player.h"
#include "../events/EventDispatcher.h"
#include <iostream>

using namespace std;

Player::Player() : Sprite("player", "./resources/character/Idle_1.png") {
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

void Player::update(std::set<SDL_Scancode> pressedKeys) {
    Sprite::update(pressedKeys);
}

void Player::draw(AffineTransform& at) {
    Sprite::draw(at);
}

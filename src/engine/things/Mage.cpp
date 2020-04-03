#include "Mage.h"
#include "MageAttack.h"
#include <math.h>
#include <iostream>
#include "../events/EventDispatcher.h"

Mage::Mage() : Sprite("mage", "./resources/assets/Animated_Sprites/Enemies/Mage/Mage.png") {
    hasCollision = true;
}

void Mage::changeHealth(int amount) {
    if (health + amount < 100) {
        health += amount;
    } else {
        health = 100;
    }
}

MageAttack* Mage::attack(Sprite* target) {
    MageAttack* attack = new MageAttack();
    attack->position = this->position;
    attack->targetPos = target->position;
    double angle = asin((target->position.x - attack->position.x)/distance(attack->position, target->position));
    attack->distX = 6*sin(angle);
    attack->distY = 6*cos(angle);
    if (target->position.y - attack->position.y < 0) {
        attack->distY *= -1;
    }

    return attack;
}

void Mage::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Mage::draw(AffineTransform& at) {
    Sprite::draw(at);
}

double Mage::distance(SDL_Point& p1, SDL_Point& p2) {
    return std::sqrt(((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.x - p1.x) * (p2.x - p1.x)));
}

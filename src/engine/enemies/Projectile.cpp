#include "Projectile.h"
#include <math.h>

Projectile::Projectile(std::string id, std::string filepath, int velocity) : Sprite(id, filepath){
    hasCollision = true;
    this->velocity = velocity;
}

void Projectile::fire(double angle){
    deltaX = velocity * cos(angle);
    deltaY = velocity * -sin(angle);
    firing = true;
}

void Projectile::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(firing){
        this->position.x+=deltaX;
        this->position.y+=deltaY;
    }
}
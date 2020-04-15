#include "Projectile.h"

#include <cmath>
#include <iostream>

Projectile::Projectile(std::string id, std::string filepath, int velocity) : Sprite(id, filepath){
    hasCollision = true;
    this->velocity = velocity;
    this->firing = false;
    this->direction = 0.0;
    this->deltaX = 0;
    this->deltaY = 0;
}

void Projectile::fire(double angle){
    deltaX = velocity * cos(angle * PI / 180);
    deltaY = velocity * -sin(angle * PI / 180);
    firing = true;
}

void Projectile::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(firing){
        this->position.x+=deltaX;
        this->position.y+=deltaY;
    }
    Sprite::update(pressedKeys,joystickState,pressedButtons);
}

double Projectile::distance(SDL_Point& p1, SDL_Point& p2) {
    return std::sqrt(((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.x - p1.x) * (p2.x - p1.x)));
}


double Projectile::aim(DisplayObject* targetSprite){ //Cause a lot of enemies need to aim :)
    //Just finds the angle between the center of the DO given(may be self, may be a Projectile, etc) and the Player
    SDL_Point target = targetSprite->getGlobalPosition();
    //std::cout<<"Target"<<target.x<<","<<target.y<<"\n";
    SDL_Point center = this->getGlobalPosition();
    //std::cout<<"Center"<<center.x<<","<<target.y<<"\n";
    double y = (target.y - center.y);
    double x = (target.x - center.x);
    double goalAngle = atan2(-y, x);
    goalAngle = goalAngle * 180 / PI;
    return goalAngle;
}

void Projectile::reflect(){
    this->deltaX = -deltaX;
    this->deltaY = -deltaY;
}
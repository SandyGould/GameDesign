#include "CannonBall.h"

int cannonball_count = 1;

CannonBall::CannonBall(int velocity):Projectile("canonball" + std::to_string(cannonball_count),"./resources/assets/Display_Objects/cannonball.png",velocity){
    cannonball_count++;
    this->type = "cannonball";
    this->saveType = this->type;
    this->scaleX = 2;
    this->scaleY= 2;
}
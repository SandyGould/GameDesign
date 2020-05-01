#include "CannonBall.h"

CannonBall::CannonBall(int velocity):Projectile("canonball","./resources/assets/Display_Objects/cannonball.png",velocity){
    this->type = "cannonball";
    this->saveType = this->type;
    this->scaleX = 2;
    this->scaleY= 2;
}
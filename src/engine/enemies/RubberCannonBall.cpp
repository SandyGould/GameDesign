#include "RubberCannonBall.h"

RubberCannonBall::RubberCannonBall(int velocity):Projectile("no","not now",velocity){
    this->type = "rubber_cannonball";
    this->saveType = this->type;
}
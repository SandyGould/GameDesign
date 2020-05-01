#include "RubberCannonBall.h"

RubberCannonBall::RubberCannonBall(int velocity):Projectile("rubber_canonball","./resources/assets/Display_Objects/rubber_cannonball.png",velocity){
    this->type = "rubber_cannonball";
    this->saveType = this->type;
    this->scaleX = 2;
    this->scaleY= 2;
}
#include "RubberCannonBall.h"

static int rubber_cannonball_count = 1;

RubberCannonBall::RubberCannonBall(int velocity):Projectile("rubber_canonball" + std::to_string(rubber_cannonball_count),"./resources/assets/Display_Objects/rubber_cannonball.png",velocity){
    rubber_cannonball_count++;
    this->type = "rubber_cannonball";
    this->saveType = this->type;
    this->scaleX = 2;
    this->scaleY= 2;
}
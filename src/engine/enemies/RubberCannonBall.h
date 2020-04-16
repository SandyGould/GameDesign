#ifndef RUBBERCANNONBALL_H
#define RUBBERCANNONBALL_H
#include "Projectile.h"

class RubberCannonBall: public Projectile{
    public:
    RubberCannonBall(int velocity);
    //This will override collision
    //We need to keep track of bounces :)
    //We need a reflect() method for when there is a collison.
    int bounce = 0;
};
#endif

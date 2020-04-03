//This is my parent Projectiles Class.
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"
#include "../events/Collision.h"
#include "../events/Event.h"

class Projectile : public Sprite{

    public:
    Projectile(std::string id, std::string filepath);
    double velocity;
    double direction; //absolute with respect to the 
    void fire(); //Every projectile will need to fire at some point

};

#endif
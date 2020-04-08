//This is my parent Projectiles Class.
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"
#include "../events/Collision.h"
#include "../events/Event.h"

class Projectile : public Sprite{

    public:
    Projectile(std::string id, std::string filepath, int velocity);
    double velocity;
    void fire(double angle); //Every projectile will need to fire at some point
    bool firing;
    int deltaX;
    int deltaY;

    virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
};

#endif
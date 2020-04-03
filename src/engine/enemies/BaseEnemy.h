#ifndef BASEENEMEY_H
#define BASEENEMY_H

#include "../AnimatedSprite.h"
#include "../events/EventListener.h"
#include "../events/EventDispatcher.h"

class BaseEnemy : public AnimatedSprite, public EventListener, public EventDispatcher{

public:

    BaseEnemy();

    virtual void update(std::set<SDL_Scancode> pressedKeys);
    virtual void draw(AffineTransform& at);
    
    //Info about the Enemies' state
    int health = 100; 
    int state = 0;

    //Should we clean this?
    bool clean = false;

};

#endif
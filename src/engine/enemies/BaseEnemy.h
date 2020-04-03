#ifndef BASEENEMEY_H
#define BASEENEMY_H

#include "../AnimatedSprite.h"
#include "../events/EventListener.h"
#include "../events/EventDispatcher.h"
#include "../things/Player.h"

class BaseEnemy : public AnimatedSprite, public EventListener, public EventDispatcher{

public:

    BaseEnemy();

    virtual void update(std::set<SDL_Scancode> pressedKeys);
    virtual void draw(AffineTransform& at);
    virtual void onCollision(DisplayObject* other);

    Player* player;
    //Info about the Enemies' state
    int health = 100; 
    int state = 0;

    //Should we clean this?
    bool clean = false;

};

#endif
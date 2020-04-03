#ifndef BASEENEMEY_H
#define BASEENEMY_H

#include "../Sprite.h"

class BaseEnemy : public Sprite, public EventListener, public EventDispatcher{

public:

    BaseEnemy();

    virtual void update(std::set<SDL_Scancode> pressedKeys);
    virtual void draw(AffineTransform& at);

private:

    int health; 
    int state;

};

#endif
#ifndef BASEENEMEY_H
#define BASEENEMY_H

#include "../AnimatedSprite.h"
#include "../events/EventListener.h"
#include "../events/EventDispatcher.h"
#include "../things/Player.h"

class BaseEnemy : public AnimatedSprite{

public:

    BaseEnemy(std::string id);

    virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
    void draw(AffineTransform& at) override;
//    void onCollision(DisplayObject* other) override;

    //Knowing about the player is nice :)
    Player* player;

    //Info about the Enemies' state
    int health = 100; 
    int state = 0;

    //Should we clean this?
    bool clean = false;

};

#endif
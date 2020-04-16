#ifndef RUBBERCANNONEER_H
#define RUBBERCANNONEER_H

#include "BaseEnemy.h"
#include "RubberCannonBall.h"

class RubberCannoneer : public BaseEnemy{
    public:
        RubberCannoneer(Player* player);
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
        Projectile* cannonball;
    private:
        int wait = 0;
};

#endif

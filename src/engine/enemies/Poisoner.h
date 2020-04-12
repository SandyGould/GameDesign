#ifndef POISONER_H
#define POISONER_H
#include "BaseEnemy.h"
#include "PoisonBomb.h"

class Poisoner : public BaseEnemy{
    public:
        Poisoner(Player* player);
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
    private:
        int actionFrames;
        int xVelocity;
        int yVelocity;
};

#endif
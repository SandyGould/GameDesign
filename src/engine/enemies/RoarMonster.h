#ifndef ROARMONSTER_H
#define ROARMONSTER_H

#include "BaseEnemy.h"
#include <cmath>
#include "Roar.h"

class RoarMonster : public BaseEnemy{
    public:
        RoarMonster(Player* player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        Roar* myAttack;
    private:
        int actionFrames = 10;
        double xVelocity = 0;
        double yVelocity = 0;
        double actualPosX = 0;
        double actualPosY = 0;
};

#endif

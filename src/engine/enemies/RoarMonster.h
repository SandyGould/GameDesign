#ifndef ROARMONSTER_H
#define ROATMONSTER_H

#include "BaseEnemy.h"
#include <cmath>

class RoarMonster : public BaseEnemy{
    public:
        RoarMonster(Player* player);
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;

    private:
        int actionFrames = 10;
        double xVelocity = 0;
        double yVelocity = 0;
        double actualPosX = 0;
        double actualPosY = 0;
};

#endif
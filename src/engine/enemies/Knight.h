#ifndef KNIGHT_H
#define KNIGHT_H

#include "BaseEnemy.h"

class Knight : public BaseEnemy{
    public:
        Knight(Player* player);
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;

    public:
        int actionFrames = 0;
        SDL_Point playerLoc = {0,0};
        int directionX = 0;
        int directionY = 0;
};

#endif

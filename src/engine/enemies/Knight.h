#ifndef KNIGHT_H
#define KNIGHT_H

#include "BaseEnemy.h"

class Knight : public BaseEnemy{
    public:
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
};

#endif
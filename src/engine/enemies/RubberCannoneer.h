#ifndef RUBBERCANNONEER_H
#define RUBBBERCANNONEER_H

#include "Cannoneer.h"
#include "RubberCannonBall.h"

class RubberCannoneer : public Cannoneer{
    public:
        RubberCannoneer();
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
    private:
        int wait = 0;
};

#endif
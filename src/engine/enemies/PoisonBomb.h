#ifndef POISONBOMB_H
#define POISONBOMB_H

#include "../Sprite.h"

class PoisonBomb : public Sprite{
    public:
        PoisonBomb();
        int radius;
        int timer = 100;
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void explode();
        int explosionTime = 6;
        virtual ~PoisonBomb();
};
#endif
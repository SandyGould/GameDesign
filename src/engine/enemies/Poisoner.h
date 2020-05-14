#ifndef POISONER_H
#define POISONER_H
#include "../projectiles/PoisonBomb.h"
#include "BaseEnemy.h"

class Poisoner : public BaseEnemy{
    public:
        Poisoner(std::shared_ptr<Player> player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    private:
        int actionFrames;
        int xVelocity;
        int yVelocity;
};

#endif
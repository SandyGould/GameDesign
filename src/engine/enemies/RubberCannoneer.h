#ifndef RUBBERCANNONEER_H
#define RUBBERCANNONEER_H

#include "BaseEnemy.h"
#include "RubberCannonBall.h"

class RubberCannoneer : public BaseEnemy{
    public:
        RubberCannoneer(std::shared_ptr<Player> player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        std::shared_ptr<Projectile> cannonball;
    private:
        int wait = 0;
};

#endif

#ifndef CANNONEER_H
#define CANNONEER_H

#include "../projectiles/Projectile.h"
#include "BaseEnemy.h"

class Cannoneer : public BaseEnemy{

    public:
        explicit Cannoneer(std::shared_ptr<Player> player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        std::shared_ptr<Projectile> cannonball;
        std::shared_ptr<Sprite> cannon;
    private:
        int wait = 0;
};
#endif
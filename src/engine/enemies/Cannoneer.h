#ifndef CANNONEER_H
#define CANNONEER_H

#include "BaseEnemy.h"
#include "Projectile.h"

class Cannoneer : public BaseEnemy{

    public:
        Cannoneer(Player* player);
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
        Projectile* cannonball;
    private:
        int wait = 0;
};
#endif
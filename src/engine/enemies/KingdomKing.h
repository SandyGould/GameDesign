#ifndef KINGDOMKING_H
#define KINGDOMKING_H

#include "../projectiles/Arrow.h"
#include "../projectiles/MageAttack.h"
#include "BaseEnemy.h"

#include <cmath>

class KingdomKing : public BaseEnemy{
    public:
        KingdomKing(std::shared_ptr<Player> player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;
    private:
        int actionFrames = 0;
        SDL_Point playerLoc = {0,0};
        int directionX = 0;
        int directionY = 0;
        double velocity;
        double direction;
        bool firing;
        int deltaX;
        int deltaY;
        void fire(double angle); //Every projectile will need to fire at some point
        void reflect();
        double aim(std::shared_ptr<DisplayObject> targetSprite);
        std::shared_ptr<Arrow> arrow;
    	std::shared_ptr<MageAttack> mageAttack;

};

#endif
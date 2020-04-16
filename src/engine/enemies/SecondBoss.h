#ifndef SECONDBOSS_H
#define SECONDBOSS_H

#include "Projectile.h"
#include "BaseEnemy.h"

class SecondBoss : public BaseEnemy{
    public:
        SecondBoss(Player* player);
        int health = 300;
        void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
        double aim(DisplayObject* targetSprite);
        void fire(double angle);
        void bounce();
        bool onCollision(DisplayObject* other) override;

    private:
        int velocity = 50;
        int deltaX = 0;
        int deltaY = 0;
        bool firing =false;
        int actionFrames = 0;
        SDL_Point playerLoc = {0,0};
        int directionX = 0;
        int directionY = 0;
        int bounces;
};

#endif
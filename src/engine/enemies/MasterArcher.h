#ifndef MASTERARCHER_H
#define MASTERARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class MasterArcher: public BaseEnemy{
    public:
        MasterArcher(Player* player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void draw(AffineTransform& at) override;
        //void onCollision(DisplayObject* other);// override;

    private:

        int coolDownFrames = -1;
        int generateCoolDown();

        int actionFrames;
        double goalAngle;
        SDL_Point target;
        Projectile* arrowParent;
        Arrow* arrow1;
        Arrow* arrow2;
        Arrow* arrow3;
};

#endif
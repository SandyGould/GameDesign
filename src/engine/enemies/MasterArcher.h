#ifndef MASTERARCHER_H
#define MASTERARCHER_H

#include "Arrow.h"
#include "BaseEnemy.h"

class MasterArcher: public BaseEnemy{
    public:
        explicit MasterArcher(std::shared_ptr<Player> player);
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void draw(AffineTransform& at) override;
        bool onCollision(std::shared_ptr<DisplayObject> other) override;

    private:

        int coolDownFrames = -1;
        int generateCoolDown();

        int actionFrames;
        double goalAngle;
        SDL_Point target;
        std::shared_ptr<Projectile> arrowParent;
        std::vector<std::shared_ptr<Arrow>> arrows;
        std::shared_ptr<Arrow> arrow1;
        std::shared_ptr<Arrow> arrow2;
        std::shared_ptr<Arrow> arrow3;
};

#endif
#ifndef OGRE_H
#define OGRE_H

#include "../projectiles/Arrow.h"
#include "BaseEnemy.h"

class Ogre : public BaseEnemy {

    public:

        Ogre(std::shared_ptr<Player> player);

        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        bool onCollision(std::shared_ptr<DisplayObject> other) override;

    private:

        int coolDownFrames = -1;
        int generateCoolDown();
        int directionX = 0;
        int directionY = 0;
        int actionFrames = 0;
        std::shared_ptr<Arrow> arrow;
    };


#endif

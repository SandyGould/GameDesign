#ifndef CHEST_H
#define CHEST_H

#include "../AnimatedSprite.h"

class Chest : public AnimatedSprite {

    public:
        Chest();

        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void draw(AffineTransform& at) override;
        bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

    private:
};

#endif

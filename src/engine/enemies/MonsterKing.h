#ifndef MONSTERKING_H
#define MONSTERKING_H

#include "../projectiles/IceAttack.h"
#include "BaseEnemy.h"

class MonsterKing : public BaseEnemy {
    public:
        MonsterKing(std::shared_ptr<Player> player);

        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void draw(AffineTransform& at) override;
        bool onCollision(std::shared_ptr<DisplayObject> other) override;
    private:
        int coolDownFrames = -1;
        int ready = 0;
        int generateCoolDown();
        int directionX = 0;
        int directionY = 0;
        int stunFrames = 0;
        int rushFrames = 0;
        int maxWalkFrames = 0;

        std::shared_ptr<IceAttack> iceAttack;
        std::shared_ptr<BaseEnemy> minion1;
        std::shared_ptr<BaseEnemy> minion2;

};

#endif

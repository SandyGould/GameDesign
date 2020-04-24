#ifndef MONSTERKING_H
#define MONSTERKING_H

#include "BaseEnemy.h"
#include "IceAttack.h"

class MonsterKing : public BaseEnemy {
    public:
        MonsterKing(Player* player);

        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
        void draw(AffineTransform& at) override;
        bool onCollision(DisplayObject* other) override;
    private:
        int coolDownFrames = -1;
        int ready = 0;
        int generateCoolDown();
        int directionX = 0;
        int directionY = 0;
        int stunFrames = 0;
        int rushFrames = 0;
        int maxWalkFrames = 0;

        IceAttack* iceAttack;
        BaseEnemy* minion1;
        BaseEnemy* minion2;

};

#endif

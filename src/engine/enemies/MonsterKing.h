#ifndef MONSTERKING_H
#define MONSTERKING_H

#include "BaseEnemy.h"

class MonsterKing : public BaseEnemy{
    public:
        void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    private:


};

#endif
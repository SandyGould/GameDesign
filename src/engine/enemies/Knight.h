#ifndef KNIGHT_H
#define KNIGHT_H

#include "BaseEnemy.h"

class Knight : public BaseEnemy {
public:
    explicit Knight(std::shared_ptr<Player> player);
    Knight(std::string id, std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName);

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

private:
    int actionFrames = 0;
    SDL_Point playerLoc = {0,0};
    int directionX = 0;
    int directionY = 0;
    int cooldown = 0;
};

#endif

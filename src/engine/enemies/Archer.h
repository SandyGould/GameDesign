#ifndef ARCHER_H
#define ARCHER_H

#include "../projectiles/Arrow.h"
#include "BaseEnemy.h"

class Archer : public BaseEnemy {

public:

    explicit Archer(std::shared_ptr<Player> player);
    Archer(std::string id, std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName);

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform& at) override;
    bool onCollision(std::shared_ptr<DisplayObject> other) override;

private:

    int coolDownFrames = -1;
    int generateCoolDown();

    int actionFrames;
    std::shared_ptr<Arrow> arrow;
};


#endif

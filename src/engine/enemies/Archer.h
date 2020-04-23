#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Archer : public BaseEnemy {

public:

explicit Archer(Player* player);
Archer(Player* player, std::string filepath, std::string xml);

void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
void draw(AffineTransform& at) override;
bool onCollision(DisplayObject* other) override;

private:

int coolDownFrames = -1;
int generateCoolDown();

int actionFrames;
Arrow* arrow;
};


#endif
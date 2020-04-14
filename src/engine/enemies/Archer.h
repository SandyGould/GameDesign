#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Archer : public BaseEnemy {

public:

Archer(Player* player);
Archer(Player* player, std::string filepath);


void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
void draw(AffineTransform& at) override;
bool onCollision(DisplayObject* other);

private:

int coolDownFrames = -1;
int generateCoolDown();

int actionFrames;
Arrow* arrow;
};


#endif
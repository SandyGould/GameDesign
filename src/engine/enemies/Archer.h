#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Archer : public BaseEnemy {

public:

Archer(Player* player);


void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
void draw(AffineTransform& at) override;
//void onCollision(DisplayObject* other);// override;

private:

int coolDownFrames = -1;
int generateCoolDown();

int actionFrames;
Arrow* arrow;
};


#endif
#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Archer : public BaseEnemy {

public:

void update(std::set<SDL_Scancode> pressedKeys) override;
void draw(AffineTransform& at) override;


private:

int coolDownFrames;
int generateCoolDown();

int actionFrames;
double goalAngle;

Arrow* arrow;
};


#endif
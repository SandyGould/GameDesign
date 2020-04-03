#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Archer : public BaseEnemy {

public:

void update(std::set<SDL_Scancode> pressedKeys) override;
void draw(AffineTransform& at) override;
void onCollision(DisplayObject* other) override;

private:

int coolDownFrames;
int generateCoolDown();

int actionFrames;
double goalAngle;
SDL_Point target;
Arrow* arrow;
};


#endif
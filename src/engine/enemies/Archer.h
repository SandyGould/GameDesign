#ifndef ARCHER_H
#define ARCHER_H

#include "BaseEnemy.h"

class Archer : public BaseEnemy {

public:

void update(std::set<SDL_Scancode> pressedKeys) override;
void draw(AffineTransform& at) override;

};


#endif
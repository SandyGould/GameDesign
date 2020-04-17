#ifndef OGRE_H
#define OGRE_H

#include "BaseEnemy.h"
#include "Arrow.h"

class Ogre : public BaseEnemy {

public:

Ogre(Player* player);

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

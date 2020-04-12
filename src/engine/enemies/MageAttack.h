#ifndef MAGEATTACK_H
#define MAGEATTACK_H

#include "Projectile.h"

class MageAttack : public Projectile {

public:
	MageAttack();
    double target;
    void fire();
};

#endif

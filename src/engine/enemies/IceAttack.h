#ifndef ICEATTACK_H
#define ICEATTACK_H

#include "Projectile.h"

class IceAttack : public Projectile {

public:
	IceAttack();
    double target;
    void fire();
};

#endif

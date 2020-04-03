#ifndef ARROW_H
#define ARROW_H

#include "Projectile.h"

class Arrow: public Projectile{

    public:

    Arrow();
    
    void drawBack();
    void fire();

};

#endif
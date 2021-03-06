#ifndef ARROW_H
#define ARROW_H

#include "Projectile.h"

class Arrow: public Projectile{
public:
    explicit Arrow(int velocity);
    void drawBack();
    int drawBackX;
    int drawBackY;

    void draw(AffineTransform& at) override;
};

#endif

#ifndef ARROW_H
#define ARROW_H

#include "Projectile.h"

class Arrow: public Projectile{

    public:

    Arrow(int velocity);
    void drawBack();
    int drawBackX;
    int drawBackY;

    void draw(AffineTransform& at) override;
    double aim(std::shared_ptr<DisplayObject> targetSprite);
};

#endif

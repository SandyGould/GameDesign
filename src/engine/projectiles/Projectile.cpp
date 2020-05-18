#include "Projectile.h"

#include <cmath>
#include <iostream>

Projectile::Projectile(std::string id, std::string filepath, int velocity) : Sprite(id, filepath){
    hasCollision = true;
    this->velocity = velocity;
    this->firing = false;
    this->deltaX = 0.0;
    this->deltaY = 0.0;
    this->storedDeltaX = 0.0;
    this->storedDeltaY = 0.0;
}

void Projectile::fire(double angle){
    deltaX = velocity * cos(angle);
    deltaY = velocity * -sin(angle);
    firing = true;
}

void Projectile::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if (Game::instance->paused) {
        return;
    }

    if (firing) {
        // Need to account for decimals
        this->storedDeltaX += deltaX;
        this->storedDeltaY += deltaY;

        // Round towards zero (truncate)
        this->position.x += static_cast<int>(storedDeltaX);
        this->storedDeltaX -= static_cast<int>(storedDeltaX);

        this->position.y += static_cast<int>(storedDeltaY);
        this->storedDeltaY -= static_cast<int>(storedDeltaY);
    }

    lifetime--;
    if (lifetime == 0) {
        this->removeThis();
    }
    Sprite::update(pressedKeys,joystickState,pressedButtons);
}

double Projectile::distance(SDL_Point& p1, SDL_Point& p2) {
    return std::sqrt(((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.x - p1.x) * (p2.x - p1.x)));
}

// TODO: account for the target's velocity :)))))
double Projectile::aim(std::shared_ptr<DisplayObject> target){ //Cause a lot of enemies need to aim :)
    //Just finds the angle between the center of the DO given(may be self, may be a Projectile, etc) and the Player
    SDL_Point pos;
    SDL_Point targetPos;

    // Get the centers!
    if (this->hitboxType == HitboxType::Rectangle) {
        Hitbox hitbox = this->getHitbox();
        pos = {(hitbox.ul.x + hitbox.ur.x) / 2, (hitbox.ul.y + hitbox.ll.y) / 2};

        if (target->hitboxType == HitboxType::Rectangle) {
            hitbox = target->getHitbox();
            targetPos = {(hitbox.ul.x + hitbox.ur.x) / 2, (hitbox.ul.y + hitbox.ll.y) / 2};
        } else {
            Hitcircle hitcircle = target->getHitcircle();
            targetPos = hitcircle.center;
        }
    } else {
        Hitcircle hitcircle = this->getHitcircle();
        pos = hitcircle.center;

        if (target->hitboxType == HitboxType::Rectangle) {
            Hitbox hitbox = target->getHitbox();
            targetPos = {(hitbox.ul.x + hitbox.ur.x) / 2, (hitbox.ul.y + hitbox.ll.y) / 2};
        } else {
            hitcircle = target->getHitcircle();
            targetPos = hitcircle.center;
        }
    }

    double y = targetPos.y - pos.y;
    double x = targetPos.x - pos.x;
    return atan2(-y, x);
}

void Projectile::reflect(double speedMult, double deltaX, double deltaY) {
    if (!reflected){
        this->reflected = true;
        this->velocity *= speedMult;
        double angle = atan2(-deltaY, deltaX);
        this->deltaX = velocity * cos(angle);
        this->deltaY = velocity * -sin(angle);
    }
}

#include "Projectile.h"

Projectile::Projectile(std::string id, std::string filepath) : Sprite(id, filepath){
    hasCollision = true;
}
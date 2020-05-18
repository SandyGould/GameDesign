#include "Shield.h"

#include "../enemies/BaseEnemy.h"

#include <iostream>

Shield::Shield()
    : Sprite("shield", "./resources/assets/Display_Objects/Shield.png") {
    hasCollision = true;
    this->type = "shield";
    this->saveType = this->type;

    this->width = 10;
    this->height = 70;
}

void Shield::switchType() {
    this->magic = !this->magic;
    this->imgPath = this->magic ? "./resources/assets/Display_Objects/MShield.png"
                                : "./resources/assets/Display_Objects/Shield.png";
    loadTexture(this->imgPath);
    this->width = 10;
    this->height = 70;
}

void Shield::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    if (this->bashFrames > 0) {
        bashFrames--;
    } else {
        this->bashing = false;
    }
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

bool Shield::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    if (this->visible) {
        auto projectile = std::dynamic_pointer_cast<Projectile>(other);
        if (projectile && this->magic == projectile->magic) {
            // https://stackoverflow.com/a/573206/5661593
            // FIXME: Does not work when you & the projectile are travelling in the same direction
            // (it will still attempt to "reflect" the projectile in the opposite direction...)
            double normalAngle = this->rotation;
            if (direction1 == CollisionDirection::Left) {
                normalAngle += PI;
            } else if (direction1 == CollisionDirection::Top) {
                normalAngle += PI / 2;
            } else if (direction1 == CollisionDirection::Bottom) {
                normalAngle += 3 * PI / 2;
            }
            double temp = (projectile->deltaX * std::cos(normalAngle) +
                           projectile->deltaY * std::sin(normalAngle)) /
                          (std::cos(normalAngle) * std::cos(normalAngle) +
                           std::sin(normalAngle) * std::sin(normalAngle));
            std::array<double, 2> u = {temp * std::cos(normalAngle), temp * std::sin(normalAngle)};
            std::array<double, 2> w = {projectile->deltaX - u[0], projectile->deltaY - u[1]};
            std::array<double, 2> reflectedVelocity = {w[0] - u[0], w[1] - u[1]};
            if (dynamic_cast<Player*>(this->parent)->slidin) {
                projectile->reflect(1.5, reflectedVelocity[0], reflectedVelocity[1]);
            } else {
                projectile->reflect(1.2, reflectedVelocity[0], reflectedVelocity[1]);
            }
        }

        if (this->bashing) {
            auto enemy = std::dynamic_pointer_cast<BaseEnemy>(other);
            if (enemy) {
                this->bashing = false;
                enemy->changeHealth(-35);
            }
        }
    }
    return true;
}

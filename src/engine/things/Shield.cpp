#include "Shield.h"

#include "../enemies/BaseEnemy.h"

constexpr int BASH_COOLDOWN = 40;
constexpr int BASH_DISTANCE = 35;
constexpr int SWITCH_COOLDOWN = 40;

Shield::Shield()
    : Sprite("shield", "./resources/assets/Display_Objects/Shield.png") {
    hasCollision = true;
    this->type = "shield";
    this->saveType = this->type;

    this->width = 10;
    this->height = 70;
}

void Shield::switchType() {
    this->switchCooldown = SWITCH_COOLDOWN;
    this->magic = !this->magic;
    this->imgPath = this->magic ? "./resources/assets/Display_Objects/MShield.png"
                                : "./resources/assets/Display_Objects/Shield.png";
    loadTexture(this->imgPath);
    this->width = 10;
    this->height = 70;
}

void Shield::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    if (this->bashFrames > 0) {
        this->bashFrames--;
    } else {
        this->bashing = false;
    }

    if (this->bashCooldown > 0) {
        this->bashCooldown--;
    }

    if (this->switchCooldown > 0) {
        this->switchCooldown--;
    }
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Shield::bash() {
    this->bashing = true;
    this->bashFrames = 3;
    this->bashCooldown = BASH_COOLDOWN;
    auto shieldBash = std::make_unique<Tween>("shield_bash", shared_from_this());
    shieldBash->animate(TweenableParams::X, this->position.x, this->position.x + BASH_DISTANCE * std::cos(this->rotation), 0, 3);
    shieldBash->animate(TweenableParams::X, this->position.x + BASH_DISTANCE * std::cos(this->rotation), this->position.x, 3, 18);
    shieldBash->animate(TweenableParams::Y, this->position.y, this->position.y + BASH_DISTANCE * std::sin(this->rotation), 0, 3);
    shieldBash->animate(TweenableParams::Y, this->position.y + BASH_DISTANCE * std::sin(this->rotation), this->position.y, 3, 18);
    TweenJuggler::getInstance().add(std::move(shieldBash));
}

bool Shield::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    if (this->visible) {
        auto* player = dynamic_cast<Player*>(this->parent);
        auto projectile = std::dynamic_pointer_cast<Projectile>(other);
        if (projectile && this->magic == projectile->magic && !projectile->reflected) {
            // https://stackoverflow.com/a/573206/5661593
            // With some extra logic to detect when you run into the projectile
            // rather than the projectile running into you
            double normalAngle = this->rotation;
            if (direction1 == CollisionDirection::Left) {
                normalAngle += PI;
                if (std::cos(normalAngle) < 0 == projectile->deltaX < 0) {
                    projectile->deltaX *= -1;
                }
            } else if (direction1 == CollisionDirection::Top) {
                normalAngle += 3 * PI / 2;
                if (std::sin(normalAngle) < 0 == projectile->deltaY < 0) {
                    projectile->deltaY *= -1;
                }
            } else if (direction1 == CollisionDirection::Bottom) {
                normalAngle += PI / 2;
                if (std::sin(normalAngle) < 0 == projectile->deltaY < 0) {
                    projectile->deltaY *= -1;
                }
            } else {
                if (std::cos(normalAngle) < 0 == projectile->deltaX < 0) {
                    projectile->deltaX *= -1;
                }
            }

            double temp = (projectile->deltaX * std::cos(normalAngle) +
                           projectile->deltaY * std::sin(normalAngle)) /
                          (std::cos(normalAngle) * std::cos(normalAngle) +
                           std::sin(normalAngle) * std::sin(normalAngle));
            std::array<double, 2> u = {temp * std::cos(normalAngle), temp * std::sin(normalAngle)};
            std::array<double, 2> w = {projectile->deltaX - u[0], projectile->deltaY - u[1]};
            std::array<double, 2> reflectedVelocity = {w[0] - u[0], w[1] - u[1]};
            if (player->slideDirection != SlideDirection::None) {
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

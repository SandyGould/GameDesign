#include "Shield.h"

#include "../enemies/BaseEnemy.h"

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

bool Shield::onCollision(std::shared_ptr<DisplayObject> other) {
    if (this->visible) {
        auto projectile = std::dynamic_pointer_cast<Projectile>(other);
        if (projectile && this->magic == projectile->magic) {
            if (dynamic_cast<Player*>(this->parent)->slidin) {
                projectile->reflect(1.5);
            } else {
                projectile->reflect(1.2);
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

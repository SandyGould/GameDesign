#include "Shield.h"
#include <iostream>
#include "../enemies/Projectile.h"
#include "../enemies/BaseEnemy.h"

Shield::Shield() : Sprite("shield", "./resources/assets/Display_Objects/Shield.png") {
    hasCollision = true;
    this->type = "shield";
    this->saveType = this->type;
}

void Shield::switchType() {
    if (this->magic) {
        this->imgPath = "./resources/assets/Display_Objects/Shield.png";
        loadTexture(this->imgPath);
        this->width = 10;
        this->height = 70;
        this->magic = false;
    } else {
        this->imgPath = "./resources/assets/Display_Objects/MShield.png";
        loadTexture(this->imgPath);
        this->width = 10;
        this->height = 70;
        this->magic = true;
    }
}

void Shield::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    if(this->bashFrames > 0){
        bashFrames--;
    }
    else{
        this->bashing = false;
    }
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Shield::draw(AffineTransform& at) {
    Sprite::draw(at);
}

bool Shield::onCollision(std::shared_ptr<DisplayObject> other){
    if(this->visible && (other->type == "arrow" || other->type== "mage_attack" || other->type == "cannonball" || other->type=="rubber_cannonball" || other->type=="ice_attack")){
        if (this->magic == std::static_pointer_cast<Projectile>(other)->magic) {
            std::static_pointer_cast<Projectile>(other)->reflect();
        }
    }
    if(bashing){
        if(other->type == "enemy" || other->type == "ogre" || other->type == "knight"){
            this->bashing = false;
            std::static_pointer_cast<BaseEnemy>(other)->changeHealth(-35);
        }
    }
    return true;
}

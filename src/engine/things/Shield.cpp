#include "Shield.h"

#include "../enemies/Projectile.h"

Shield::Shield() : Sprite("shield", "./resources/assets/Display_Objects/Shield.png") {
    hasCollision = true;
    this->type = "shield";
    this->saveType = this->type;
}

void Shield::switchType() {
    if (this->magic) {
        this->imgPath = "./resources/assets/Display_Objects/Shield.png";
        loadTexture(this->imgPath, Game::renderer);
        this->magic = false;
    } else {
        this->imgPath = "./resources/assets/Display_Objects/MShield.png";
        loadTexture(this->imgPath, Game::renderer);
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

bool Shield::onCollision(DisplayObject* other){
    if(other->type == "arrow" || other->type== "mage_attack" || other->type == "cannonball" || other->type=="rubber_cannonball"){
        dynamic_cast<Projectile*>(other)->reflect();
    }
    return true;
}
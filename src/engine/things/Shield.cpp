#include "Shield.h"

#include "../enemies/Projectile.h"

Shield::Shield() : Sprite("shield", "./resources/assets/Display_Objects/Shield.png") {
    hasCollision = true;
    this->type = "shield";
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

void Shield::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Shield::draw(AffineTransform& at) {
    Sprite::draw(at);
}

bool Shield::onCollision(DisplayObject* other){
    if(other->type == "arrow" || other->type== "mage_attack" || other->type == "cannonball" || other->type=="rubber_cannonball"){
        dynamic_cast<Projectile*>(other)->reflect();
    }
    return false;
}
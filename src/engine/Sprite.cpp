#include "Sprite.h"

Sprite::Sprite(std::string id, SDL_Renderer *r) : DisplayObject(id) {
    this->type = "Sprite";
    this->saveType = this->type;
    this->renderer = r;
}

Sprite::Sprite(std::string id, std::string filepath, SDL_Renderer *r) : DisplayObject(id, filepath, r) {
    this->type = "Sprite";
    this->saveType = this->type;
    this->renderer = r;
}

Sprite::Sprite(std::string id, int red, int green, int blue, SDL_Renderer *r) : DisplayObject(id, red, green, blue) {
    this->type = "Sprite";
    this->saveType = this->type;
    this->renderer = r;
}

Sprite::Sprite(const DisplayObject& other) : DisplayObject(other.id){
    if (other.type == "Sprite"){
        Sprite* S = (Sprite*) &other;
        this->id = S->id + "_copy";
        this->type = S->type;
        this->saveType = S->saveType;
        this->renderer = S->renderer;
        this->position = S->position;
        this->width = S->width;
        this->height = S->height;
        this->pivot = S->pivot;
        this->scaleX = S->scaleX;
        this->scaleY = S->scaleY;
        this->rotation = S->rotation;
        this->facingRight = S->facingRight;
        this->hasCollision = S->hasCollision;
        this->imgPath = S->imgPath;
        this->loadTexture(this->imgPath);
    } else{
        this->type = "Sprite";
        this->id = "FAILED_COPY";
        this->renderer = Game::renderer;
    }
}

void Sprite::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Sprite::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}

Sprite::~Sprite(){
}

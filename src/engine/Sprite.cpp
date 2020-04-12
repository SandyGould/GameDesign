#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(std::string id, SDL_Renderer *r) : DisplayObject(id) {
    this->type = "Sprite";
    this->r = r;
}

Sprite::Sprite(std::string id, std::string filepath, SDL_Renderer *r) : DisplayObject(id, filepath, r) {
    this->type = "Sprite";
    this->r = r;
}

Sprite::Sprite(std::string id, int red, int green, int blue, SDL_Renderer *r) : DisplayObject(id, red, green, blue) {
    this->type = "Sprite";
    this->r = r;
}

Sprite::Sprite(const DisplayObject& other) : DisplayObject(other.id){
    if (other.type == "Sprite"){
        Sprite* S = (Sprite*) &other;
        this->id = S->id + "_copy";
        this->type = S->type;
        this->r = S->r;
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
        this->loadTexture(this->imgPath, Game::renderer);
    } else{
        this->type = "Sprite";
        this->id = "FAILED_COPY";
        this->r = Game::renderer;
    }
}

void Sprite::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Sprite::draw(AffineTransform& at) {
    Sprite::draw(at, Game::renderer);
}

void Sprite::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    DisplayObject::draw(at, r, src);
}

Sprite::~Sprite(){
}

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(std::string id) : DisplayObject(id) {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, std::string filepath) : DisplayObject(id, filepath) {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "Sprite";
}

void Sprite::update(std::unordered_set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
}

void Sprite::draw(AffineTransform& at) {
    Sprite::draw(at, Game::renderer);
}

void Sprite::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    DisplayObject::draw(at, r, src);
}

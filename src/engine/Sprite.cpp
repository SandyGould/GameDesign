#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : DisplayObjectContainer() {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, std::string filepath) : DisplayObjectContainer(id, filepath) {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "Sprite";
}

void Sprite::update(std::unordered_set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Sprite::draw(AffineTransform& at) {
    Sprite::draw(at, Game::renderer);
}

void Sprite::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    DisplayObjectContainer::draw(at);
}

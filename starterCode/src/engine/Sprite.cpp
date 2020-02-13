#include "Sprite.h"

Sprite::Sprite() : DisplayObjectContainer() {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, std::string filepath) : DisplayObjectContainer(id, filepath) {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "Sprite";
}

void Sprite::update(std::set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void Sprite::draw(AffineTransform& at) {
    DisplayObjectContainer::draw(at);
}
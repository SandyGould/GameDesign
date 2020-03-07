#include "Sprite.h"

Sprite::Sprite() : DisplayObject() {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, std::string filepath) : DisplayObject(id, filepath) {
    this->type = "Sprite";
}

Sprite::Sprite(std::string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "Sprite";
}

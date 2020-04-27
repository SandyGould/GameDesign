#include "Sprite.h"

#include <iostream>

Sprite::Sprite(const std::string& id, SDL_Renderer* r) : DisplayObject(id) {
    this->type = "Sprite";
    this->saveType = this->type;
    this->renderer = r;
}

Sprite::Sprite(const std::string& id, const std::string& path, SDL_Renderer* r) : DisplayObject(id, path, r) {
    this->type = "Sprite";
    this->saveType = this->type;
}

Sprite::Sprite(const std::string& id, int red, int green, int blue, SDL_Renderer* r) : DisplayObject(id, red, green, blue) {
    this->type = "Sprite";
    this->saveType = this->type;
    this->renderer = r;
}

Sprite* Sprite::clone() {
    std::cout << "SPRITE" << std::endl;
    auto* clone = new Sprite(this->id + "_copy", this->renderer);
    clone->position = this->position;
    clone->width = this->width;
    clone->height = this->height;
    clone->pivot = this->pivot;
    clone->scaleX = this->scaleX;
    clone->scaleY = this->scaleY;
    clone->rotation = this->rotation; // in radians
    clone->facingRight = this->facingRight;
    clone->hasCollision = this->hasCollision;
    clone->visible = this->visible;
    clone->type = this->type;
    clone->imgPath = this->imgPath;
    clone->saveType = this->saveType;
    clone->loadTexture(clone->imgPath);

    for (const auto& child : this->children) {
        clone->addChild(std::shared_ptr<DisplayObject>(child->clone()));
    }

    return clone;
}

void Sprite::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Sprite::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}

#include "Crosshair.h"
#include "../events/EventDispatcher.h"

Crosshair::Crosshair() : Sprite("crosshair", "./resources/other/crosshair.png") {
    hasCollision = true;
}

void Crosshair::update(std::unordered_set<SDL_Scancode> pressedKeys) {
    Sprite::update(pressedKeys);
}

void Crosshair::draw(AffineTransform& at) {
    Sprite::draw(at);
}

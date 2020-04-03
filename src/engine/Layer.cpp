#include "Layer.h"
#include "Game.h"
#include <iostream>

Layer::Layer() : DisplayObject("layer") {
    this->type = "Layer";
}

Layer::Layer(std::string id) : DisplayObject(id) {
    this->type = "Layer";
}

// void Layer::applyTransformations(AffineTransform& at) {
//     at.translate(position.x + parallaxSpeed, position.y + parallaxSpeed);
//     at.rotate(rotation);
//     at.scale(scaleX, scaleY);
//     at.translate(-pivot.x, -pivot.y);
// }

// void Layer::reverseTransformations(AffineTransform& at) {
//     at.translate(pivot.x, pivot.y);
//     at.scale(1.0 / scaleX, 1.0 / scaleY);
//     at.rotate(-rotation);
//     at.translate(-position.x - parallaxSpeed, -position.y - parallaxSpeed);
// }

// void Layer::draw(AffineTransform& at) {
//     Layer::draw(at, Game::renderer);
// }

// void Layer::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
//             std::cout << id << ": " << position.x << std::endl;

//     applyTransformations(at);
//         std::cout << id << ": " << position.x << std::endl;

//     // this->position.x *= this->parallaxSpeed;
//     // this->position.y *= this->parallaxSpeed;
//     std::cout << id << ": " << position.x << std::endl;
//     std::cout << parallaxSpeed << std::endl;
//     at.translate(pivot.x, pivot.y);
//     for (auto child : children) {
//         child->draw(at, r);
//     }
//     at.translate(-pivot.x, -pivot.y);

//     reverseTransformations(at);
// }

// void Layer::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
//     if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
// 		pivot.x *= parallaxSpeed;
// 	}
// 	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
//         pivot.x /= parallaxSpeed;
// 	}
// 	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
// 		pivot.y *= parallaxSpeed;
// 	}
// 	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
// 		pivot.y /= parallaxSpeed;
// 	}
//     DisplayObject::update(pressedKeys, joystickState, pressedButtons);
// }

void Layer::draw(AffineTransform& at) {
    Layer::draw(at, Game::renderer);
}

void Layer::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    // at.translate(position.x * parallaxSpeed, position.y * parallaxSpeed);
    // DisplayObject::draw(at, r, src);
    // at.translate(-position.x * parallaxSpeed, -position.y * parallaxSpeed);
    
    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (auto child : children) {
        child->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}

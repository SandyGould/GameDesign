#include "Layer.h"
#include "Game.h"
#include <iostream>

Layer::Layer() : DisplayObject("layer") {
    this->type = "layer";
}

Layer::Layer(std::string id) : DisplayObject(id) {
    this->type = "layer";
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

void Layer::setParallax(){
    // Either set "at" position so that children also gets affected (at.translate...)
    // Or just set the position of this layer object (position.x *= parallaxSpeed)
    position.x = -cam->pivot.x * parallaxSpeed;
    // position.y = orig_position.y -cam->pivot.y * parallaxSpeed;
    std::cout << "Camera pivot x: " << cam->pivot.x << std::endl;
    std::cout << "Camera pivot y: " << cam->pivot.y << std::endl;
}

void Layer::draw(AffineTransform& at) {
    Layer::setParallax();
    Layer::draw(at, Game::renderer);
}

void Layer::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    // at.translate(position.x * parallaxSpeed, position.y * parallaxSpeed);
    // DisplayObject::draw(at, r, src);
    // at.translate(-position.x * parallaxSpeed, -position.y * parallaxSpeed);
    Layer::setParallax();

    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (auto child : children) {
        // at.translate(- cam->pivot.x * parallaxSpeed, - cam->pivot.y * parallaxSpeed);
        // child->position.x = child->orig_position.x - cam->pivot.x * parallaxSpeed;
        // child->position.y = child->orig_position.y - cam->pivot.y * parallaxSpeed;
        child->draw(at);
        // at.translate(-(- cam->pivot.x * parallaxSpeed), -(- cam->pivot.y * parallaxSpeed));
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}

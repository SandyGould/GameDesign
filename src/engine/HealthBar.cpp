#include "HealthBar.h"

#include <string>
#include <iostream>

HealthBar::HealthBar(std::string id) : HealthBar(id, 0, 255, 0) {

}

HealthBar::HealthBar(std::string id, int red, int green, int blue) : HealthBar(id, red, green, blue, 150, 30) {
    
}

HealthBar::HealthBar(std::string id, int red, int green, int blue, int w, int h) : DisplayObject(id, red, green, blue, w, h) {
    // starting health percentage
    this->healthPerc = 1;
}

// for loading a health bar frame graphic - will finish later
// HealthBar::HealthBar(std::string id, std::string filepath){
//     this->currHealth = 100;
// }

HealthBar::~HealthBar() {

}

void HealthBar::scaleHealth(double change) {
    if (this->healthPerc + change >= 0 && this->healthPerc + change <= 1)  {
        this->healthPerc = this->healthPerc + change;
        this->scaleX = healthPerc;
        std::cout << "Your current health is: " << this->healthPerc << std::endl;
    }
    else {
        std::cout << "Sorry, you're dead! " << std::endl;
    }
    
}

void HealthBar::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void HealthBar::draw(AffineTransform& at) {
    DisplayObject::draw(at, Game::renderer);
}

void HealthBar::draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src) {
    DisplayObject::draw(at, r, src);
}
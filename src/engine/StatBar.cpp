#include "StatBar.h"

#include <string>
#include <iostream>

StatBar::StatBar(std::string id) : StatBar(id, 0, 255, 0) {

}

StatBar::StatBar(std::string id, int red, int green, int blue) : StatBar(id, red, green, blue, 150, 30) {
    
}

StatBar::StatBar(std::string id, int red, int green, int blue, int w, int h) : DisplayObject(id, red, green, blue, w, h) {
    // starting Stat percentage
    this->StatPerc = 1;
}

// for loading a Stat bar frame graphic - will finish later
// StatBar::StatBar(std::string id, std::string filepath){
//     this->currStat = 100;
// }

StatBar::~StatBar() {

}

void StatBar::scaleStat(double change) {
    if (this->StatPerc + change >= 0 && this->StatPerc + change <= 1)  {
        this->StatPerc = this->StatPerc + change;
        this->scaleX = StatPerc;
        std::cout << "Your current health is: " << this->StatPerc << std::endl;
    }
    else {
        std::cout << "Sorry, you're dead! " << std::endl;
    }
}

void StatBar::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void StatBar::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}
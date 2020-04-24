#include "StatBar.h"

#include <string>
#include <iostream>

StatBar::StatBar(std::string id, std::shared_ptr<Player> player) : StatBar(id, 0, 255, 0, player) {
}

StatBar::StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player) : StatBar(id, red, green, blue, player, 150, 30) {
}

StatBar::StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player, int w, int h) : DisplayObject(id, red, green, blue, w, h) {
    this->player = player;
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

void StatBar::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void StatBar::updateHealth(){
    // Player health always maxed at 100
    if (this->player->health > 0){
        this->scaleX = player->health * 0.01; // Convert 100 -> 1 scale
        std::cout << "Your current health is: " << player->health << std::endl;
    }
    else{
        this->scaleX = 0;
        std::cout << "Sorry, you're dead! " << std::endl;
        // Potentially add a tween fade out for player
        // EventDispatch death screen
    }

}


void StatBar::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}
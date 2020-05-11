#include "StatBar.h"

#include <iostream>
#include <string>

StatBar::StatBar(std::string id, std::shared_ptr<Player> player) : StatBar(id, 0, 255, 0, player) {
}

StatBar::StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player) : StatBar(id, red, green, blue, player, 150, 30) {
}

StatBar::StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player, int w, int h) : DisplayObject(id) {
    this->player = player;
    this->StatPerc = 1;
    this->bar = std::make_shared<DisplayObject>(id, 255, 0, 0);
    this->addChild(bar);
}


// for loading a Stat bar frame graphic - will finish later
StatBar::StatBar(std::string id, std::string filepath, std::shared_ptr<Player> player) : DisplayObject(id) {
    this->player = player;
    this->StatPerc = 1;
    
    this->bar = std::make_shared<DisplayObject>(id + "_bar", 255, 0, 0, 195, 15);
    this->bar->position = {40,460}; 
    // this->bar->ss = 25;
    // this->bar->scaleY = 0.15;
    
    this->frame = std::make_shared<DisplayObject>(id + "_frame", filepath);
    this->frame->position = {0,355};
    this->frame->scaleX = 2;
    this->frame->scaleY = 2;
    
    this->addChild(frame);
    this->addChild(bar);
}

StatBar::~StatBar() {

}

void StatBar::scaleStat(double change) {
    if (this->StatPerc + change >= 0 && this->StatPerc + change <= 1)  {
        this->StatPerc = this->StatPerc + change;
        this->bar->scaleX = StatPerc;
        // std::cout << "Your current health is: " << this->StatPerc << std::endl;
    }
    else {
        // std::cout << "Sorry, you're dead! " << std::endl;
    }
}

void StatBar::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void StatBar::updateHealth(){
    // Player health always maxed at 100
    if (this->player->health > 0){
        this->bar->scaleX = player->health * 0.01; // Convert 100 -> 1 scale
        // std::cout << "Your current health is: " << player->health << std::endl;
    }
    else{
        this->bar->scaleX = 0;
        // std::cout << "Sorry, you're dead! " << std::endl;
        // Potentially add a tween fade out for player
        // EventDispatch death screen
    }

}


void StatBar::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}
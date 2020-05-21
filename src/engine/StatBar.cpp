#include "StatBar.h"

// for loading a Stat bar frame graphic - will finish later
StatBar::StatBar(std::string id, std::string filepath, double max, int red, int green, int blue) : DisplayObject(id) {
    this->StatPerc = 1;
    this->max = max;

    this->bar = std::make_shared<DisplayObject>(id + "_bar", red, green, blue, 195, 15);
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

void StatBar::setStat(double amount) {
    this->StatPerc = std::clamp(amount / this->max, 0.0, 1.0);
    this->bar->scaleX = this->StatPerc;
}

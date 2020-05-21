#include "StatBar.h"

static int stat_bar_count = 0;

StatBar::StatBar(const std::string& id, const std::string& filepath,
                 int* stat, int max,
                 int red, int green, int blue) : DisplayObject(id) {
    this->stat = stat;
    this->max = max;

    this->bar = std::make_shared<DisplayObject>(id + "_bar", red, green, blue, 195, 15);
    this->bar->position = {40 + stat_bar_count * (this->bar->width + 40), 460};

    this->frame = std::make_shared<DisplayObject>(id + "_frame", filepath);
    this->frame->position = {0 + stat_bar_count * (this->bar->width + 40),355};
    this->frame->scaleX = 2;
    this->frame->scaleY = 2;

    this->addChild(frame);
    this->addChild(bar);

    stat_bar_count++;
}

void StatBar::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    this->bar->scaleX = std::clamp(*stat / static_cast<double>(this->max), 0.0, 1.0);
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

#include "StatBar.h"

static int stat_bar_count = 0;

StatBar::StatBar(const std::string& id, const std::string& filepath, double max,
                 int red, int green, int blue) : DisplayObject(id) {
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

void StatBar::setStat(double amount) {
    this->bar->scaleX = std::clamp(amount / this->max, 0.0, 1.0);
}

#pragma once

#include "DisplayObject.h"

class StatBar : public DisplayObject {
public:
    StatBar(const std::string& id, const std::string& filepath, double max,
            int red, int green, int blue);

    void setStat(double amount);

private:
    double max;

    std::shared_ptr<DisplayObject> bar;
    std::shared_ptr<DisplayObject> frame;
};

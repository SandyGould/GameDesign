#pragma once

#include "DisplayObject.h"

class StatBar : public DisplayObject {
public:
    StatBar(std::string id, std::string filepath, double max, int red, int green, int blue);

	void scaleStat(double change);
    void setStat(double amount);

private:
    double StatPerc;
    double max;
    std::shared_ptr<DisplayObject> bar;
    std::shared_ptr<DisplayObject> frame;
};

#pragma once

#include "DisplayObject.h"

class StatBar : public DisplayObject {
public:
    StatBar(const std::string& id, const std::string& filepath,
            int* stat, int max,
            int red, int green, int blue);

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

private:
    int* stat;
    int max;

    std::shared_ptr<DisplayObject> bar;
    std::shared_ptr<DisplayObject> frame;
};

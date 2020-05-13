#pragma once

#include "../DisplayObject.h"

using namespace std;

class SelectionMenuBase : public DisplayObject {
public:
	SelectionMenuBase();
    explicit SelectionMenuBase(const std::string& id);

    void update(const std::unordered_set<SDL_Scancode> &pressedKeys, const jState &joystickState, const std::unordered_set<Uint8> &pressedButtons) override;

    bool active = false;
};

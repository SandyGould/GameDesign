#pragma once

#include "../engine/things/SelectionMenuBase.h"
#include "../engine/things/SelectionMenuOption.h"

#include <SDL2/SDL_ttf.h>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

class TitleScreen : public Game {
public:
    std::shared_ptr<SelectionMenuBase> selection_menu_base;
    std::shared_ptr<SelectionMenuOption> selection_quit_option;
    std::shared_ptr<SelectionMenuOption> selection_resume_option;

    TitleScreen();

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform& at) override;

    void handleEvent(Event* e) override;

private:
    
};

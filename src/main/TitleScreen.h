#pragma once

#include "../engine/DisplayObject.h"

#include <SDL2/SDL_ttf.h>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include "../engine/events/EventListener.h"
#include "../engine/things/SelectionMenuBase.h"
#include "../engine/things/SelectionMenuOption.h"
#include "../engine/events/KeyDownEvent.h"
#include "../engine/events/GameStartEvent.h"
#include "../engine/events/GameQuitEvent.h"
#include "../engine/events/MouseDownEvent.h"
#include "../engine/things/TextBox.h"
#include "./Rooms.h"



class TitleScreen: public Game {
public:
    /* Singleton pattern */
    //static Game* instance;

    /* The global DisplayObject container */
    //std::shared_ptr<DisplayObject> container;



    std::shared_ptr<SelectionMenuBase> selection_menu_base;
    std::shared_ptr<SelectionMenuOption> selection_quit_option;
    std::shared_ptr<SelectionMenuOption> selection_resume_option;

    bool release = false;

    //Global frame counter
    static unsigned int frameCounter;

    TitleScreen();

    void start();

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform& at) override;
    void begin();
    //bool paused = false;
    // This happens after drawing but before rendering
    //virtual void draw_post(){};
    void handleEvent(Event* e) override;

private:
    
};

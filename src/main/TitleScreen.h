#pragma once

#include "DisplayObject.h"

#include <SDL2/SDL_ttf.h>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include "./Events/EventListener.h"
#include "./things/SelectionMenuBase.h"
#include "./things/SelectionMenuOption.h"
#include "../engine/events/KeyDownEvent.h"
#include "../engine/events/MouseDownEvent.h"
#include "./things/TextBox.h"



class TitleScreen: public EventListener {
public:
    /* Singleton pattern */
    //static Game* instance;

    /* The global DisplayObject container */
    std::shared_ptr<DisplayObject> container;



    std::shared_ptr<SelectionMenuBase> selection_menu_base;
    std::shared_ptr<SelectionMenuOption> selection_quit_option;
    std::shared_ptr<SelectionMenuOption> selection_resume_option;

    bool release = false;

    //Global frame counter
    static unsigned int frameCounter;

    TitleScreen();

    void start();

    virtual void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons);
    virtual void draw(AffineTransform& at);
    void begin();
    //bool paused = false;
    // This happens after drawing but before rendering
    //virtual void draw_post(){};
    void handleEvent(Event* e) override;

private:
    
};

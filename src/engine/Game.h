#pragma once

#include "DisplayObject.h"

#include <SDL2/SDL_ttf.h>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include "./events/EventListener.h"
//#include "./TitleScreen.h"


enum class MouseState {
    NONE,
    CLICKING,
    //START,
    //DRAGGING,
    DRAGGING,
    //END,
};

class Game : public EventListener {
public:
    /* Singleton pattern */
    static Game* instance;

    /* The global DisplayObject container */
    std::shared_ptr<DisplayObject> container;



    

    int frames_per_sec = 60;
    int windowWidth, windowHeight;

    SDL_Window* window;
    static SDL_Renderer* renderer;
    static TTF_Font* font;
    SDL_GameController* gameController = NULL;

    //Global frame counter
    static unsigned int frameCounter;

    Game(int windowWidth, int windowHeight);
    virtual ~Game();

    void start();

    virtual void clearRenderers();
    virtual void presentRenderers();

    virtual void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons);
    virtual void draw(AffineTransform& at);

    bool paused = false;
    // This happens after drawing but before rendering
    virtual void draw_post(){};
    void handleEvent(Event* e) override;

private:
    std::unordered_set<SDL_Scancode> pressedKeys;

    void initSDL();
    void quitSDL();

    const int JOYSTICK_DEAD_ZONE = 8000; //We can change this to have a better feel later!
    jState joystickState = {0, 0};

    std::unordered_set<Uint8> pressedButtons;
    std::map<std::string, int> joystickMovement;

    MouseState mouseState;

    SDL_Keymod modifiers;
};

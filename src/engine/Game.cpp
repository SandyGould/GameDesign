#include "Game.h"

#include "events/DragEvent.h"
#include "events/DragStartEvent.h"
#include "events/KeyDownEvent.h"
#include "events/MouseDownEvent.h"
#include "events/MouseMotionEvent.h"
#include "events/MouseUpEvent.h"
#include "events/MouseWheelEvent.h"
#include "events/TextEditEvent.h"
#include "events/TextInputEvent.h"
#include "events/WindowEnterEvent.h"
#include "events/WindowExitEvent.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std;

SDL_Renderer* Game::renderer;
TTF_Font* Game::font;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight) {
    Game::instance = this;

    this->container = std::make_shared<DisplayObject>("game");
    this->container->type = "game";
    this->container->saveType = this->container->type;

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    this->mouseState = MouseState::NONE;
    this->modifiers = KMOD_NONE;

    initSDL();
    TTF_Init();
    font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 24);
}

Game::~Game() {
    // Delete ourselves before SDL destroys our renderer
    this->container.reset();

    quitSDL();
}

void Game::quitSDL() {
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(window);
    SDL_GameControllerClose(gameController);
    gameController = NULL;

    IMG_Quit();
    SDL_Quit();
}

void Game::initSDL() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    // In theory this will go through every "Joystick" in and open the first controller.
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            gameController = SDL_GameControllerOpen(i); //opens the first controller.
            if (gameController) {                       //checks to make sure the controller opened correctly.
                break;
            }
            //We could throw an error after this but lol no :)
        }
    }
    window = SDL_CreateWindow("Rebound",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              this->windowWidth, this->windowHeight,
                              0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_StopTextInput();

    Game::renderer = renderer;
}

void Game::start() {
    cout << "got to start" << endl;
    milliseconds ms_per_frame(1000ms / this->frames_per_sec);
    auto start = steady_clock::now();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        auto end = steady_clock::now();
        milliseconds duration = duration_cast<milliseconds>(end - start);
        if (duration > ms_per_frame) {
            start = end;
            cout << "going to update" << endl;
            this->update(pressedKeys, joystickState, pressedButtons);
            cout << "done updating" << endl;
            AffineTransform at;
            cout << "going to draw" << endl;
            this->draw(at);
        }

        // While there are events to process:
        cout << "ok getting events now" << endl;
        while (SDL_PollEvent(&event)) {
            cout << "checking event type" << endl;
            switch (event.type) {
            case SDL_QUIT:
                cout << "it's quit" << endl;
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                cout << "it's a window event" << endl;
                if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                    quit = true;
                } else if (event.window.event == SDL_WINDOWEVENT_ENTER) {
                    this->modifiers = SDL_GetModState();
                    EventDispatcher::getInstance().dispatchEvent(new WindowEnterEvent(event.window.windowID, this->modifiers));
                } else if (event.window.event == SDL_WINDOWEVENT_LEAVE) {
                    this->modifiers = SDL_GetModState();
                    EventDispatcher::getInstance().dispatchEvent(new WindowExitEvent(event.window.windowID, this->modifiers));
                }
                break;
            case SDL_KEYDOWN:
                cout << "it's a keydown" << endl;
                pressedKeys.insert(event.key.keysym.scancode);
                EventDispatcher::getInstance().dispatchEvent(new KeyDownEvent());
                break;
            case SDL_KEYUP:
                cout << "it's a keyup" << endl;
                this->pressedKeys.erase(event.key.keysym.scancode);
                break;
            case SDL_MOUSEBUTTONDOWN:
                cout << "it's a mouse down" << endl;
                this->modifiers = SDL_GetModState();
                EventDispatcher::getInstance().dispatchEvent(new MouseDownEvent(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.windowID, this->modifiers));
                this->mouseState = MouseState::CLICKING;
                break;
            case SDL_MOUSEBUTTONUP:
                cout << "it's a mouse up" << endl;
                if (this->mouseState == MouseState::CLICKING) {
                    EventDispatcher::getInstance().dispatchEvent(new MouseUpEvent(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.windowID, this->modifiers));
                    // We could throw in a ClickEvent here if we needed to
                }

                // Or a DragEndEvent

                this->mouseState = MouseState::NONE;
                break;
            case SDL_MOUSEMOTION:
                cout << "THE MOUSE MOVED" << endl;
                this->modifiers = SDL_GetModState();
                EventDispatcher::getInstance().dispatchEvent(new MouseMotionEvent(event.motion.x, event.motion.y, event.motion.windowID, this->modifiers));

                if (this->mouseState == MouseState::CLICKING) {
                    this->mouseState = MouseState::DRAGGING;
                    EventDispatcher::getInstance().dispatchEvent(new DragStartEvent(event.motion.x, event.motion.y));
                }

                if (this->mouseState == MouseState::DRAGGING) {
                    EventDispatcher::getInstance().dispatchEvent(new DragEvent(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, event.motion.windowID, this->modifiers));
                }
                break;
            case SDL_MOUSEWHEEL:
                cout << "it's the mouse wheel" << endl;
                EventDispatcher::getInstance().dispatchEvent(new MouseWheelEvent(event.wheel.x, event.wheel.y, event.wheel.windowID));
                break;
            case SDL_TEXTINPUT:
                this->modifiers = SDL_GetModState();
                EventDispatcher::getInstance().dispatchEvent(new TextInputEvent(event.text.text, event.text.windowID, this->modifiers));
                break;
            case SDL_TEXTEDITING:
                this->modifiers = SDL_GetModState();
                EventDispatcher::getInstance().dispatchEvent(new TextEditEvent(event.edit.text, event.edit.start, event.edit.length, event.edit.windowID, this->modifiers));
                break;
            case SDL_JOYAXISMOTION:
                if (event.jaxis.axis == 0) { //On the x axis.
                    this->joystickState.xVal1 = event.jaxis.value;
                } else if (event.jaxis.axis == 1) {
                    this->joystickState.yVal1 = event.jaxis.value;
                } else if (event.jaxis.axis == 3) { //On the x axis.
                    this->joystickState.xVal2 = event.jaxis.value;
                } else if (event.jaxis.axis == 4) {
                    this->joystickState.yVal2 = event.jaxis.value;
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                this->pressedButtons.insert(event.cbutton.button);
                break;
            case SDL_CONTROLLERBUTTONUP:
                this->pressedButtons.erase(event.cbutton.button);
                break;
            }
        }
    }
}

void Game::clearRenderers() {
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Game::renderer);
}

void Game::presentRenderers() {
    SDL_RenderPresent(Game::renderer);
}

void Game::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    frameCounter++;
    cout << "updating container" << endl;
    this->container->update(pressedKeys, joystickState, pressedButtons);
    cout << "done updating container" << endl;
}

void Game::draw(AffineTransform& at) {
    this->clearRenderers();
    this->container->draw(at);
    this->draw_post();
    this->presentRenderers();
}

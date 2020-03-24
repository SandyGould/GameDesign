#include "Game.h"

#include "events/DragEvent.h"
#include "events/DragStartEvent.h"
#include "events/MouseDownEvent.h"
#include "events/MouseUpEvent.h"
#include "events/DragEvent.h"
#include "events/WindowEnterEvent.h"
#include "events/WindowExitEvent.h"
#include "events/MouseMotionEvent.h"
#include "events/TextInputEvent.h"
#include "events/TextEditEvent.h"
#include "events/MouseWheelEvent.h"

#include <chrono>
#include <iostream>

using namespace std::chrono;

SDL_Renderer* Game::renderer;
TTF_Font* Game::font;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight) : DisplayObject("game") {
	Game::instance = this;
	
	this->type = "Game";

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->mouseState = MouseState::NONE;

	initSDL();
	TTF_Init();
	font = TTF_OpenFont("./resources/fonts/open-sans/OpenSans-Regular.ttf", 24);
}

Game::~Game() {
	quitSDL();
}

void Game::quitSDL() {
	SDL_DestroyRenderer(Game::renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void Game::initSDL() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Rebound",
	                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                          this->windowWidth, this->windowHeight,
	                          SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_StopTextInput();

	Game::renderer = renderer;
}

void Game::start() {
	milliseconds ms_per_frame(1000ms / this->frames_per_sec);
	auto start = steady_clock::now();

	bool quit = false;
	SDL_Event event;

	while (!quit) {
		auto end = steady_clock::now();
		milliseconds duration = duration_cast<milliseconds>(end - start);
		if (duration > ms_per_frame) {
			start = end;
			this->update(pressedKeys);
			AffineTransform at;
			this->draw(at);
		}

		// While there are events to process:
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_CLOSE){
					quit = true;
				} else if (event.window.event == SDL_WINDOWEVENT_ENTER){
					this->modifiers = SDL_GetModState();
					this->dispatcher.dispatchEvent(new WindowEnterEvent(event.window.windowID, this->modifiers));
				} else if (event.window.event == SDL_WINDOWEVENT_LEAVE){
					this->modifiers = SDL_GetModState();
					this->dispatcher.dispatchEvent(new WindowExitEvent(event.window.windowID, this->modifiers));
				}
				break;
			case SDL_KEYDOWN:
				pressedKeys.insert(event.key.keysym.scancode);
				break;
			case SDL_KEYUP:
				this->pressedKeys.erase(event.key.keysym.scancode);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->modifiers = SDL_GetModState();
				this->dispatcher.dispatchEvent(new MouseDownEvent(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.windowID, this->modifiers));
				this->mouseState = MouseState::CLICKING;
				break;
			case SDL_MOUSEBUTTONUP:
				if (this->mouseState == MouseState::CLICKING) {
					this->dispatcher.dispatchEvent(new MouseUpEvent(event.button.x, event.button.y, event.button.button, event.button.clicks, event.button.windowID, this->modifiers));
					// We could throw in a ClickEvent here if we needed to
				}

				// Or a DragEndEvent

				this->mouseState = MouseState::NONE;
				break;
			case SDL_MOUSEMOTION:
				this->modifiers = SDL_GetModState();
				this->dispatcher.dispatchEvent(new MouseMotionEvent(event.motion.x, event.motion.y, event.motion.windowID, this->modifiers));

				if (this->mouseState == MouseState::CLICKING) {
					this->mouseState = MouseState::DRAGGING;
					this->dispatcher.dispatchEvent(new DragStartEvent(event.motion.x, event.motion.y));
				}

				if (this->mouseState == MouseState::DRAGGING) {
					this->dispatcher.dispatchEvent(new DragEvent(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel, event.motion.windowID, this->modifiers));
				}
				break;
			case SDL_MOUSEWHEEL:
				this->dispatcher.dispatchEvent(new MouseWheelEvent(event.wheel.x, event.wheel.y, event.wheel.windowID));
				break;
			case SDL_TEXTINPUT:
				this->modifiers = SDL_GetModState();
				this->dispatcher.dispatchEvent(new TextInputEvent(event.text.text, event.text.windowID, this->modifiers));
				break;
			case SDL_TEXTEDITING:
				this->modifiers = SDL_GetModState();
				this->dispatcher.dispatchEvent(new TextEditEvent(event.edit.text, event.edit.start, event.edit.length, event.edit.windowID, this->modifiers));
				break;
			}
		}
	}
}

void Game::clearRenderers(){
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
}

void Game::presentRenderers(){
	SDL_RenderPresent(Game::renderer);
}

void Game::update(std::unordered_set<SDL_Scancode> pressedKeys) {
	frameCounter++;
	DisplayObject::update(pressedKeys);
}

void Game::draw(AffineTransform& at) {
	this->clearRenderers();
	DisplayObject::draw(at);
	this->draw_post();
	this->presentRenderers();
}

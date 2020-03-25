#include "Game.h"

#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;

SDL_Renderer* Game::renderer;
Game* Game::instance;
unsigned int Game::frameCounter = 0;

Game::Game(int windowWidth, int windowHeight) {
	Game::instance = this;
	
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	initSDL();
	TTF_Init();
}

Game::~Game() {
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
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
	IMG_Init(IMG_INIT_PNG);

	// In theory this will go through every "Joystick" in and open the first controller.
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
    	if (SDL_IsGameController(i)) {
       		gameController = SDL_GameControllerOpen(i); //opens the first controller.
			if (gameController) { //checks to make sure the controller opened correctly.
				break;
			}
			//We could throw an error after this but lol no :)
		}
    }
	window = SDL_CreateWindow("Rebound",
	                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                          this->windowWidth, this->windowHeight,
	                          SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

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
			this->update(pressedKeys, joystickState, pressedButtons);
			AffineTransform at;
			this->draw(at);
		}

		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			pressedKeys.insert(event.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			this->pressedKeys.erase(event.key.keysym.scancode);
			break;
		case SDL_JOYAXISMOTION:
			if(event.jaxis.axis == 0){ //On the x axis.
				this->joystickState.xVal = event.jaxis.value;
			} else if (event.jaxis.axis == 1) {
				this->joystickState.yVal = event.jaxis.value;
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

void Game::update(std::set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
	frameCounter++;
	DisplayObjectContainer::update(pressedKeys, joystickState, pressedButtons);
}

void Game::draw(AffineTransform& at) {
	SDL_RenderClear(Game::renderer);
	DisplayObjectContainer::draw(at);
	SDL_RenderPresent(Game::renderer);
}
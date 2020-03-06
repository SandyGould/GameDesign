#ifndef GAME_H
#define GAME_H

#include "DisplayObjectContainer.h"

#include <vector>
#include <set>
#include <map>

class Game : public DisplayObjectContainer {
public:
	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window* window;
	static SDL_Renderer* renderer;
	SDL_GameController* gameController = NULL;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	void update(std::set<SDL_Scancode> pressedKeys);
	//void update(std::set<SDL_Scancode> pressedKeys, std::map<std::string, int> joystickMovement);
	void draw(AffineTransform& at) override;

private:
	const int JOYSTICK_DEAD_ZONE = 8000; //We can change this to have a better feel later!
	void initSDL();
	void quitSDL();
	std::set<SDL_Scancode> pressedKeys;
	std::map<std::string, int> joystickMovement;
	
};

#endif
#ifndef GAME_H
#define GAME_H

#include "DisplayObjectContainer.h"
#include "events/EventDispatcher.h"

#include <vector>
#include <unordered_set>

class Game : public DisplayObjectContainer, public EventDispatcher {
public:
	/* Singleton pattern */
	static Game* instance;

	int frames_per_sec = 60;
	int windowWidth, windowHeight;

	SDL_Window* window;
	static SDL_Renderer* renderer;

	//Global frame counter
	static unsigned int frameCounter;

	Game(int windowWidth, int windowHeight);
	virtual ~Game();
	void start();

	void update(std::unordered_set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

private:

	void initSDL();
	void quitSDL();
	std::unordered_set<SDL_Scancode> pressedKeys;

};

#endif

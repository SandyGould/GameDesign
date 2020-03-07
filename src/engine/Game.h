#pragma once

#include "DisplayObjectContainer.h"
#include "events/EventDispatcher.h"

#include <vector>
#include <unordered_set>

enum class MouseState {
	NONE,
	CLICKING,
	//START,
	//DRAGGING,
	DRAGGING,
	//END,
};

class Game : public DisplayObjectContainer {
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

	// This happens after drawing but before rendering
	virtual void draw_post() {};

protected:
	EventDispatcher dispatcher;

private:
	std::unordered_set<SDL_Scancode> pressedKeys;

	void initSDL();
	void quitSDL();

	DisplayObject* selected;

	MouseState mouseState;

	SDL_Keymod modifiers;
};

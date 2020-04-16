#pragma once

#include "DisplayObject.h"
#include "Game.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

using namespace std;

class SelectionMenuBase : public DisplayObject, public EventListener {

public:

	SelectionMenuBase();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	void draw(AffineTransform& at);

	void handleEvent(Event* e);

private:
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
};
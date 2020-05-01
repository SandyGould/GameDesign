#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

using namespace std;

class SelectionMenuBase : public DisplayObject {

public:

	SelectionMenuBase();
	string id = "";
	void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	void handleEvent(Event* e) override;

private:
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;
};
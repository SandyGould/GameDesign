#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "TextBox.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

using namespace std;

class SelectionMenuOption : public DisplayObject, public EventListener {

public:

	inline static const std::string QUIT = "selection_menu_quit_option";
	inline static const std::string RESUME = "selection_menu_resume_option";

	SelectionMenuOption(string id, string text);

	void updateAlpha();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

	void handleEvent(Event* e) override;

private:
	TextBox * textbox;

	string text;
};
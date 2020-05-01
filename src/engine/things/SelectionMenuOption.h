#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "TextBox.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

using namespace std;

class SelectionMenuOption : public DisplayObject {

public:

	inline static const std::string QUIT = "selection_menu_quit_option";
	inline static const std::string RESUME = "selection_menu_resume_option";
	inline static const std::string START = "selection_menu_start_option";

	SelectionMenuOption(string id, string text);

	void updateAlpha();

	void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	void handleEvent(Event* e) override;

private:
	std::shared_ptr<TextBox> textbox;

	string text;
};
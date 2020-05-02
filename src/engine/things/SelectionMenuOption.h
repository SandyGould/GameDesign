#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "TextBox.h"
#include "../events/EventListener.h"

using namespace std;

class SelectionMenuOption : public DisplayObject {

public:

	inline static const std::string QUIT = "selection_menu_quit_option";
	inline static const std::string RESUME = "selection_menu_resume_option";
	inline static const std::string CONTINUE = "selection_menu_continue_option";
	inline static const std::string START = "selection_menu_start_option";

	SelectionMenuOption(string id, string text);
    ~SelectionMenuOption() override;

	void handleEvent(Event* e) override;

private:
	std::shared_ptr<TextBox> textbox;

	string text;
};
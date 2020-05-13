#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "../events/EventListener.h"
#include "SelectionMenuBase.h"
#include "TextBox.h"

using namespace std;

class SelectionMenuOption : public DisplayObject {

public:

	inline static const std::string QUIT = "quit_option";
	inline static const std::string RESUME = "resume_option";
	inline static const std::string CONTINUE = "continue_option";
	inline static const std::string START = "start_option";

    SelectionMenuOption(SelectionMenuBase* base, const string& id, const string& text);
    ~SelectionMenuOption() override;

	void handleEvent(Event* e) override;

private:
    // Options do not own the base
    SelectionMenuBase* base;

	std::shared_ptr<TextBox> textbox;

	string text;
};
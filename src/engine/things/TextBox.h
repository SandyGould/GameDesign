#pragma once

#include "../DisplayObject.h"
#include "../Game.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class TextBox : public DisplayObject {

public:
	explicit TextBox(std::string id);
    TextBox(std::string id, std::string text);
	TextBox(std::string id, std::string text, TTF_Font* font);
	TextBox(std::string id, std::string text, TTF_Font* font, SDL_Renderer* renderer);

	~TextBox() override;

	void setText(string text);
	void setColor(SDL_Color color);
	void setNextPanel();
	void addTextPanel(string text);

	bool finishedPanels();

	void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	void handleEvent(Event* e) override;

private: 
	TTF_Font* font;
	std::string text;
	SDL_Color textColor = {255, 255, 255, 0};

	vector<string> textpanels;
	int panelPos;

	// SDL_Rect* box;
};
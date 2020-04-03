#pragma once

#include "DisplayObject.h"
#include "Game.h"
#include "../events/Event.h"
#include "../events/EventListener.h"

#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class TextBox : public DisplayObject, public EventListener {

public:
	TextBox(std::string id);
    TextBox(std::string id, std::string text);
	TextBox(std::string id, std::string text, TTF_Font* font);
	TextBox(std::string id, std::string text, TTF_Font* font, SDL_Renderer* r);

	virtual ~TextBox();

	void setText(string text);
	void setColor(SDL_Color color);
	void setNextPanel();
	void addTextPanel(string text);

	bool finishedPanels();

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	void draw(AffineTransform& at);
	void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL);

	void handleEvent(Event* e);

private: 
	TTF_Font* font;
	std::string text;
	SDL_Color textColor = {255, 255, 255, 0};

	vector<string> textpanels;
	int panelPos;

	// SDL_Rect* box;
};
#pragma once

#include "DisplayObject.h"
#include "Game.h"

#include <SDL2/SDL_ttf.h>

#include <string>

class TextObject : public DisplayObject {

public:
	TTF_Font* font;
	std::string text;
	SDL_Color textColor = {255, 255, 255, 0};

    explicit TextObject(std::string id);
    TextObject(std::string id, std::string text);
	TextObject(std::string id, std::string text, TTF_Font* font);
	TextObject(std::string id, std::string text, TTF_Font* font, SDL_Renderer* r);
	// Copy constructors are a pain for now.
	// TextObject(const TextObject& other);
	~TextObject() override;

	void setText(std::string text);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:

};

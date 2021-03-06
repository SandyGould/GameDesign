#include "TextBox.h"
#include "../events/Event.h"
#include "../events/TweenEvent.h"
#include "../events/KeyDownEvent.h"
#include "../tweens/Tween.h"
#include "../tweens/TweenParam.h"
#include "../tweens/TweenJuggler.h"

#include <iostream>

using namespace std;

TextBox::TextBox(string id) : TextBox(id, "", Game::font) {
    
}

TextBox::TextBox(string id, string text) : TextBox(id, text, Game::font) {
}

TextBox::TextBox(string id, string text, TTF_Font* font) : TextBox(id, text, font, Game::renderer) {

}

TextBox::TextBox(string id, string text, TTF_Font* font, SDL_Renderer* renderer) : DisplayObject(id) {
    this->type = "TextObject";
	this->saveType = this->type;

    this->text = text;

	this->textpanels.push_back(text);
	this->panelPos = 0;

    this->font = font;

    this->renderer = renderer;

    this->setText(this->textpanels.front());
}

TextBox::~TextBox(){}

void TextBox::setText(string text){
    this->text = text;

    if (this->text.length() == 0){
        this->text = " ";
    }

    SDL_Surface* temp = TTF_RenderText_Blended_Wrapped(this->font, this->text.c_str(), textColor, 150);
    this->width = temp->w;
    this->height = temp->h;
    this->setSurface(temp);
    this->setTexture(SDL_CreateTextureFromSurface(this->renderer, temp));
}

void TextBox::setColor(SDL_Color color){
	this->textColor = color;
}

void TextBox::setNextPanel(){
	this->panelPos++;

	if(this->panelPos < this->textpanels.size()){
		this->setText(textpanels.at(panelPos));
	}
}

bool TextBox::finishedPanels(){
	//if it's at the last panel or it's past the panel
	return this->panelPos >= textpanels.size() - 1;
}

void TextBox::addTextPanel(string text){
	textpanels.push_back(text);
}

void TextBox::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void TextBox::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}

void TextBox::handleEvent(Event* e){
	if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT){
		if(((TweenEvent*) e)->getTween()->getID() == "player_tween"){
			EventDispatcher::getInstance().removeEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
			auto start_text_tween = std::make_shared<Tween>("start_text_tween", shared_from_this());
			start_text_tween->animate(TweenableParam::ALPHA, 0, 255, 0, 10, EaseType::EASE_IN);
			start_text_tween->animate(TweenableParam::SCALE_Y, 0, 1.0, 0, 10, EaseType::EASE_IN);
			start_text_tween->animate(TweenableParam::SCALE_X, 0, 1.0, 0, 10, EaseType::EASE_IN);
			TweenJuggler::getInstance().add(start_text_tween);
			EventDispatcher::getInstance().addEventListener(this, KeyDownEvent::KEY_DOWN_EVENT);
		}
	}
	else if (e->getType() == KeyDownEvent::KEY_DOWN_EVENT){
		if(finishedPanels()){
			this->alpha = 0;
			EventDispatcher::getInstance().removeEventListener(this, KeyDownEvent::KEY_DOWN_EVENT);
		} else {
			this->setNextPanel();
		}
	}
}

#include "TextObject.h"

using namespace std;

TextObject::TextObject(string id) : TextObject(id, "", Game::font) {
    
}

TextObject::TextObject(string id, string text) : TextObject(id, text, Game::font) {
    
}

TextObject::TextObject(string id, string text, TTF_Font* font) : TextObject(id, text, font, Game::renderer) {

}

TextObject::TextObject(string id, string text, TTF_Font* font, SDL_Renderer* r) : DisplayObject(id) {
    this->type = "TextObject";

    this->text = text;
    this->font = font;

    this->renderer = r;

    this->setText(this->text);
}

//Not currently supported
// TextObject::TextObject(const TextObject& other) {
    
// }

TextObject::~TextObject() {

}

void TextObject::setText(string text){
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

void TextObject::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void TextObject::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}


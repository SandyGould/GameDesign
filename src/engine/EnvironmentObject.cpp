#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject(std::string id, SDL_Renderer *r) : Sprite(id) {
	this->type = "EnvironmentObject";
	this->renderer = r;
}
EnvironmentObject::EnvironmentObject(std::string id, std::string filepath, SDL_Renderer *r) : Sprite(id, filepath) {
	this->type = "EnvironmentObject";
	this->renderer = r;
}
EnvironmentObject::EnvironmentObject(std::string id, int red, int green, int blue, SDL_Renderer *r) : Sprite(id, red, green, blue) {
	this->type = "EnvironmentObject";
	this->renderer = r;
}

EnvironmentObject* EnvironmentObject::clone() {
    auto* clone = static_cast<EnvironmentObject*>(Sprite::clone());
	clone->type = "EnvironmentObject";
    return clone;
}

EnvironmentObject::~EnvironmentObject(){
	
}

void EnvironmentObject::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void EnvironmentObject::draw(AffineTransform& at){
	DisplayObject::draw(at);
}
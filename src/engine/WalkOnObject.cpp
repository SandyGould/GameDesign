#include "WalkOnObject.h"

WalkOnObject::WalkOnObject(std::string id, SDL_Renderer *r) : EnvironmentObject(id) {
	this->type = "walk_on_object";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(std::string id, std::string filepath, SDL_Renderer *r) : EnvironmentObject(id, filepath) {
	this->type = "walk_on_object";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(std::string id, int red, int green, int blue, SDL_Renderer *r) : EnvironmentObject(id, red, green, blue) {
	this->type = "walk_on_object";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(const DisplayObject& other) : EnvironmentObject(other) {
	this->type = "walk_on_object";
}

WalkOnObject::~WalkOnObject(){
	
}

void WalkOnObject::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void WalkOnObject::draw(AffineTransform& at){
	DisplayObject::draw(at);
}
#include "HitObject.h"

HitObject::HitObject(std::string id, SDL_Renderer *r) : EnvironmentObject(id) {
	this->type = "HitObject";
	this->renderer = r;
}
HitObject::HitObject(std::string id, std::string filepath, SDL_Renderer *r) : EnvironmentObject(id, filepath) {
	this->type = "HitObject";
	this->renderer = r;
}
HitObject::HitObject(std::string id, int red, int green, int blue, SDL_Renderer *r) : EnvironmentObject(id, red, green, blue) {
	this->type = "HitObject";
	this->renderer = r;
}
HitObject::HitObject(const DisplayObject& other) : EnvironmentObject(other) {
	this->type = "HitObject";
}

HitObject::~HitObject(){
	
}

void HitObject::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void HitObject::draw(AffineTransform& at){
	DisplayObject::draw(at);
}
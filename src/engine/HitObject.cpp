#include "HitObject.h"

HitObject::HitObject(std::string id, SDL_Renderer *r) : EnvironmentObject(id) {
	this->type = "hit_object";
	this->renderer = r;
}
HitObject::HitObject(std::string id, std::string filepath, SDL_Renderer *r) : EnvironmentObject(id, filepath) {
	this->type = "hit_object";
	this->renderer = r;
}
HitObject::HitObject(std::string id, int red, int green, int blue, SDL_Renderer *r) : EnvironmentObject(id, red, green, blue) {
	this->type = "hit_object";
	this->renderer = r;
}
HitObject::HitObject(const DisplayObject& other) : EnvironmentObject(other) {
	this->type = "hit_object";
}

HitObject::~HitObject(){
	
}

void HitObject::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void HitObject::draw(AffineTransform& at){
	DisplayObject::draw(at);
}
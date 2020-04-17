#include "WalkOnObject.h"
#include "./things/Player.h"
#include <iostream>

WalkOnObject::WalkOnObject(std::string id, SDL_Renderer *r) : EnvironmentObject(id) {
	this->type = "WalkOnObject";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(std::string id, std::string filepath, SDL_Renderer *r) : EnvironmentObject(id, filepath) {
	this->type = "WalkOnObject";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(std::string id, int red, int green, int blue, SDL_Renderer *r) : EnvironmentObject(id, red, green, blue) {
	this->type = "WalkOnObject";
	this->renderer = r;
}
WalkOnObject::WalkOnObject(const DisplayObject& other) : EnvironmentObject(other) {
	this->type = "WalkOnObject";
}

WalkOnObject::~WalkOnObject(){
	
}

void WalkOnObject::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void WalkOnObject::draw(AffineTransform& at){
	DisplayObject::draw(at);
}

bool WalkOnObject::onCollision(DisplayObject* other){
	if(this->id == "shield_power_up" && other->type == "player"){
		this->visible = false;
		Player * player = dynamic_cast<Player*>(other);
		player->toggleShieldVisible(true);
		return true;
	} /*else if (this->id == "")*/
	return false;
}
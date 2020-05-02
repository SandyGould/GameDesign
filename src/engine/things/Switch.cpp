#include "Switch.h"
#include "Player.h"
#include <iostream>

Switch::Switch(SDL_Renderer *r): EnvironmentObject("Switch", "./resources/Rebound/area3_res/assets/switch_off.png"){
    this->type = "Switch";
    this->state_on = "./resources/Rebound/area3_res/assets/switch_on.png";
    this->state_off = "./resources/Rebound/area3_res/assets/switch_off.png";
    this->renderer = r;
}

Switch::~Switch(){}

void Switch::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
	DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void Switch::draw(AffineTransform& at){
	DisplayObject::draw(at);

    // Somehow without this, children of switch never actually get "drawn" even though draw() is being called
    at.translate(pivot.x, pivot.y);
    for (const auto& child : children) {
        child->draw(at);
    }
    at.translate(-pivot.x, -pivot.y);
}

bool Switch::onCollision(std::shared_ptr<DisplayObject> other){
	if(other->type == "player" && !state){
        state = true;
        this->imgPath = this->state_on;
        loadTexture(imgPath);
        /* 
        Json: Create a children array 
        Scene.cpp: Iterate through the children and add them all to temp_children 
        */
        this->children = temp_children;
		return true;
    }
    else if(state){
        return true; // Allow players to walk on the switch even after it has been turned on
    }
	return false;
}
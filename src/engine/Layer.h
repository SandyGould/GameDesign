#pragma once

#include "DisplayObject.h"
#include "Camera.h"
#include <unordered_set>
#include <string>
#include <vector>

class Layer : public DisplayObject {

public:
	Layer();
    Layer(std::string id);
	~Layer() override = default;

	// void applyTransformations(AffineTransform& at);
	// void reverseTransformations(AffineTransform& at);

	// virtual void updates(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;

	void setParallax();
	void draw(AffineTransform &at) override;
	Camera* cam;

private:
};
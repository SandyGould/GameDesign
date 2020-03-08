#pragma once

#include "DisplayObject.h"

class Sprite : public DisplayObject {

public:
	Sprite(std::string id);
	Sprite(std::string id, std::string filepath);
	Sprite(std::string id, int red, int green, int blue);
private:

};

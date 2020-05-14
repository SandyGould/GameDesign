#pragma once

#include "DisplayObject.h"
#include "Camera.h"
#include <unordered_set>
#include <string>
#include <vector>

class Layer : public DisplayObject {

public:
	Layer();
    explicit Layer(std::string id);

	void setParallax();
    void draw(AffineTransform& at) override;

private:
};
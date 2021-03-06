#pragma once

#include "DisplayObject.h"

class Camera : public DisplayObject {

public:
	Camera(int width, int height);
	~Camera() override = default;

	// limit where the camera can move
	void setRightLimit(int rightLimit);
	void setLeftLimit(int leftLimit);
	void setTopLimit(int topLimit);
	void setBottomLimit(int bottomLimit);

	// pan left and right by a certain factor
	void panRight(int factor);
	void panLeft(int factor);
	void panUp(int factor);
	void panDown(int factor);
	
	// zoom in and out by a certain factor
	void zoomIn(double factor);
	void zoomOut(double factor);

    double getZoom();

	// custom function to make following a character a little easier/neater
	void follow(int newX, int newY);

	void draw(AffineTransform &at) override;

private:
	int rightLimit;
	int leftLimit;
	int topLimit;
	int bottomLimit;
};

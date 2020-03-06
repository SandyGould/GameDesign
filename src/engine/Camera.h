#ifndef CAMERA_H
#define CAMERA_H
#include "DisplayObjectContainer.h"

#include "DisplayObjectContainer.h"

class Camera : public DisplayObjectContainer { 

public:
	Camera();
	~Camera();

	int viewportWidth = 500;
	int viewportHeight = 500;

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

	// custom function to make following a character a little easier/neater
	void follow(int newX, int newY);

	void draw(AffineTransform &at);

private:
	int rightLimit;
	int leftLimit;
	int topLimit;
	int bottomLimit;
};

#endif
#ifndef CAMERA_H
#define CAMERA_H

#include "DisplayObjectContainer.h"

class Camera : public DisplayObjectContainer { 

public:
	Camera();
	~Camera();

	int viewportWidth = 500;
	int viewportHeight = 500;

	// pan left and right by a certain factor
	void panRight(int factor);
	void panLeft(int factor);
	void panUp(int factor);
	void panDown(int factor);
	
	// zoom in and out by a certain factor
	void zoomIn(double factor);
	void zoomOut(double factor);


private:

	
};

#endif
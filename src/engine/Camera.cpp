#include "Camera.h"

Camera::Camera() : DisplayObjectContainer(){
    this->type = "Camera";
}

Camera::~Camera() {

}


void Camera::panRight(int factor) {
    this->position.x -= factor;
}

void Camera::panLeft(int factor) {
    this->position.x += factor;
}

void Camera::panUp(int factor) {
    this->position.y += factor;
}

void Camera::panDown(int factor) {
    this->position.y -= factor;
}
	
void Camera::zoomIn(double factor) {
    this->scaleX += factor;
    this->scaleY += factor;
}

void Camera::zoomOut(double factor) {
    if ((scaleX - factor > 0) && (scaleY - factor) > 0) {
        this->scaleX -= factor;
        this->scaleY -= factor;    
    }
}
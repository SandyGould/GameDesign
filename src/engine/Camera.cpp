#include <climits>
#include "Camera.h"

Camera::Camera() : DisplayObjectContainer(){
    this->type = "Camera";

    // set default limits (camera can go anywhere)
    this->topLimit = INT_MIN;
    this->bottomLimit = INT_MAX;
    this->leftLimit = INT_MIN;
    this->rightLimit = INT_MAX;

    this->width = this->viewportWidth;
    this->height = this->viewportHeight;
}

Camera::~Camera() {

}

void Camera::setRightLimit(int rightLimit) {
    this->rightLimit = rightLimit;
}

void Camera::setLeftLimit(int leftLimit) {
    this->leftLimit = leftLimit;
}

void Camera::setTopLimit(int topLimit) {
    this->topLimit = topLimit;
}

void Camera::setBottomLimit(int bottomLimit) {
    this->bottomLimit = bottomLimit;
}

void Camera::panRight(int factor) {
    if (this->pivot.x + factor <= this->rightLimit) {
        this->pivot.x += factor;
    }
}

void Camera::panLeft(int factor) {
    if (this->pivot.x - factor >= this->leftLimit) {
        this->pivot.x -= factor;
    }
}

void Camera::panUp(int factor) {
    if (this->pivot.y - factor >= this->topLimit) {
        this->pivot.y -= factor;
    }
}

void Camera::panDown(int factor) {
    if (this->pivot.y + factor <= this->bottomLimit) {
        this->pivot.y += factor;
    }
}
	
void Camera::zoomIn(double factor) {
    this->scaleX *= factor;
    this->scaleY *= factor;
}

void Camera::zoomOut(double factor) {
    // if ((scaleX - factor > 0) && (scaleY - factor) > 0) {
        this->scaleX /= factor;
        this->scaleY /= factor;    
    // }
}

void Camera::follow(int newX, int newY) {
    if (newX >= leftLimit * scaleX && newX <= rightLimit * scaleX) {
        this->pivot.x = newX;
    }
    if (newY >= topLimit *scaleY && newY <= bottomLimit * scaleY) {
        this->pivot.y = newY;
    }
}

void Camera::draw(AffineTransform& at) {
    applyTransformations(at);

    for (auto child : children) {
        child->draw(at);
    }

    reverseTransformations(at);
}

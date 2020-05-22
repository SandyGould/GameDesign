#include <climits>
#include "Camera.h"

Camera::Camera(int width, int height) : DisplayObject("camera") {
    this->type = "Camera";
    this->saveType = this->type;

    // set default limits (camera can go anywhere)
    this->topLimit = INT_MIN;
    this->bottomLimit = INT_MAX;
    this->leftLimit = INT_MIN;
    this->rightLimit = INT_MAX;

    this->width = width;
    this->height = height;
}

void Camera::setRightLimit(int rightLimit) {
    this->rightLimit = rightLimit - this->position.x;
}

void Camera::setLeftLimit(int leftLimit) {
    this->leftLimit = leftLimit + this->position.x;
}

void Camera::setTopLimit(int topLimit) {
    this->topLimit = topLimit + this->position.y;
}

void Camera::setBottomLimit(int bottomLimit) {
    this->bottomLimit = bottomLimit - this->position.y;
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

double Camera::getZoom() {
    return this->scaleX;
}

void Camera::follow(int newX, int newY) {
    this->pivot.x = std::clamp(newX, static_cast<int>(leftLimit * scaleX), static_cast<int>(rightLimit * scaleX));
    this->pivot.y = std::clamp(newY, static_cast<int>(topLimit * scaleY), static_cast<int>(bottomLimit * scaleY));
}

void Camera::draw(AffineTransform& at) {
    auto origAT = at;
    applyTransformations(at);
    for (const auto& child : children) {
        child->draw(at);
    }
    at = origAT;
}

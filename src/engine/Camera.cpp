#include <climits>
#include "Camera.h"
#include "Game.h"
#include <iostream>
#include "events/TweenEvent.h"
#include "tweens/TweenJuggler.h"

Camera::Camera() : DisplayObject("camera") {
    this->type = "Camera";

    // set default limits (camera can go anywhere)
    this->topLimit = INT_MIN;
    this->bottomLimit = INT_MAX;
    this->leftLimit = INT_MIN;
    this->rightLimit = INT_MAX;

    this->width = this->viewportWidth;
    this->height = this->viewportHeight;
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

double Camera::getZoom() {
    return this->scaleX;
}

void Camera::follow(int newX, int newY) {
    if (newX >= leftLimit * scaleX && newX <= rightLimit * scaleX) {
        this->pivot.x = newX;
    }
    if (newY >= topLimit *scaleY && newY <= bottomLimit * scaleY) {
        this->pivot.y = newY;
    }
}


// void Camera::applyTransformations(AffineTransform& at) {
// 	at.scale(scaleX, scaleY);
// 	at.rotate(rotation);
//     at.translate(position.x, position.y);
// 	at.translate(-pivot.x, -pivot.y);
// }

// void Camera::reverseTransformations(AffineTransform& at) {
// 	at.translate(pivot.x, pivot.y);
//     at.translate(-position.x, -position.y);
// 	at.rotate(-rotation);
// 	at.scale(1.0/scaleX, 1.0/scaleY);
// }

void Camera::draw(AffineTransform& at) {
    applyTransformations(at);
    for (auto child : children) {
        child->draw(at);
    }
    reverseTransformations(at);  
}

void Camera::handleEvent(Event* e){
    if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT) {
        EventDispatcher::getInstance().removeEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
        if (((TweenEvent*) e)->getTween()->getID() == "out_transition") {
            this->changeScene = true;
        }
    }
}
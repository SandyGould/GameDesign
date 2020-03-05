#include "TweenParam.h"

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time) {
    this->paramToTween = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->currVal = startVal;
}

TweenParam::~TweenParam() { }

TweenableParams TweenParam::getParam() {
    return this->paramToTween;
}

double TweenParam::getStartVal() {
    return this->startVal;
}

double TweenParam::getEndVal() {
    return this->endVal;
}

double TweenParam::getTweenTime() {
    return this->time;
}

double TweenParam::getCurrVal() {
    return this->currVal;
}

void TweenParam::setCurrVal(double value) {
    this->currVal = value;
}

bool TweenParam::isComplete(){
    // if the start value was less than the end value and the current value is now greater than/equal to end val
    if (this->startVal <= this->endVal && this->currVal >= this->endVal) {
        return true;
    }
    // if the start value was greater than the end value and the current value is now less than/equal to end val
    else if (this->startVal > this->endVal && this->currVal <= this->endVal) { 
        return true;
    }
    return false;
}
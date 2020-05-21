#include "TweenParam.h"

TweenParam::TweenParam(TweenableParam paramToTween,
                       double startVal, double endVal,
                       double startTime, double duration,
                       EaseType easeType) {
    this->paramToTween = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->startTime = startTime;
    this->duration = duration;
    this->currVal = startVal;
    this->easeType = easeType;
}

TweenableParam TweenParam::getParam() const {
    return this->paramToTween;
}

double TweenParam::getStartVal() const {
    return this->startVal;
}

double TweenParam::getEndVal() const {
    return this->endVal;
}

double TweenParam::getStartTime() const {
    return this->startTime;
}

double TweenParam::getDuration() const {
    return this->duration;
}

double TweenParam::getCurrVal() const {
    return this->currVal;
}

EaseType TweenParam::getEaseType() const {
    return this->easeType;
}

void TweenParam::setCurrVal(double value) {
    this->currVal = value;
}

void TweenParam::setCurrChange(double amtChange){
    double totalChange = this->endVal - this->startVal;
    this->currVal = this->startVal + totalChange * amtChange;
}

bool TweenParam::isComplete() const {
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

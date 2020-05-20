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

TweenableParam TweenParam::getParam() {
    return this->paramToTween;
}

double TweenParam::getStartVal() {
    return this->startVal;
}

double TweenParam::getEndVal() {
    return this->endVal;
}

double TweenParam::getStartTime() {
    return this->startTime;
}

double TweenParam::getDuration() {
    return this->duration;
}

double TweenParam::getCurrVal() {
    return this->currVal;
}

EaseType TweenParam::getEaseType(){
    return this->easeType;
}

void TweenParam::setCurrVal(double value) {
    this->currVal = value;
}

void TweenParam::setCurrChange(double amtChange){
    double totalChange = this->endVal - this->startVal;
    this->currVal = this->startVal + totalChange * amtChange;
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

#include "TweenParam.h"

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time) {
    this->paramToTween = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->currVal = startVal;
    this->easeType = TweenParam::EASE_IN_OUT;
}

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time, std::string easeType) {
    this->paramToTween = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->currVal = startVal;
    this->easeType = easeType;
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

std::string TweenParam::getEaseType(){
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
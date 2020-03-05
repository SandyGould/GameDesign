#include "Tween.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

Tween::Tween(DisplayObject* object) {
    this->currObject = object;
    this->amountChange = 0;
}

Tween::Tween(DisplayObject* object, TweenTransitions transition) {
    this->currObject = object;
    this->amountChange = 0;
}

Tween::~Tween() { 
   currTweening.clear();
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time) {
    TweenParam* temp = new TweenParam(fieldToAnimate, startVal, endVal, time);
    this->currTweening.push_back(temp);
}

void Tween::update() {
    std::list<TweenParam*>::iterator it;
    for (it = this->currTweening.begin(); it != this->currTweening.end(); it++) {
        // calculate (linear) change manually for now,
        // replace w/ transition function in the future
        this->amountChange = ((*it)->getEndVal() - (*it)->getStartVal()) / (*it)->getTweenTime();

        // update current value of the TweenParam
        this->setValue((*it)->getParam(), (*it)->getCurrVal() + this->amountChange);
        
        if ((*it)->isComplete()) { 
            this->currTweening.erase(it--); // remove the param if done w/ tweening
        }
        else {
            if ((*it)->getParam().getKey() == "ALPHA") {
                this->currObject->alpha = (*it)->getCurrVal();
            }
            if ((*it)->getParam().getKey() == "ROTATION") {
                this->currObject->rotation = (*it)->getCurrVal();    
            }
            if ((*it)->getParam().getKey() == "SCALE_X") {
                this->currObject->scaleX = (*it)->getCurrVal();
            }
            if ((*it)->getParam().getKey() == "SCALE_Y") {
                this->currObject->scaleY = (*it)->getCurrVal();
            }
            if ((*it)->getParam().getKey() == "X") {
                this->currObject->position.x = (*it)->getCurrVal();
            }
            if ((*it)->getParam().getKey() == "Y") {
                this->currObject->position.y = (*it)->getCurrVal();
            }
        }
    }
}

void Tween::setValue(TweenableParams param, double value) {
    std::list<TweenParam*>::iterator it;
    for (it = currTweening.begin(); it != currTweening.end(); it++) {
        if ((*it)->getParam().getKey() == param.getKey()) {
            (*it)->setCurrVal(value);
        }
    }
}

bool Tween::isComplete() {
    // tween is complete if no more parameters left to tween
    if (this->currTweening.size() == 0) {
        return true;
    }
    return false;
}
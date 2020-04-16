#include "Tween.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

Tween::Tween(DisplayObject* object) {
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

Tween::Tween(DisplayObject* object, TweenTransitions transition) {
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
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
    for (it = this->currTweening.begin(); it != this->currTweening.end(); ) {
        // calculate (linear) change manually for now,
        // replace w/ transition function in the future
        
        if(this->timeElapsed > (*it)->getTweenTime()){ 
            it = this->currTweening.erase(it); // remove the param if done w/ tweening
            //continue;
        }
        if (it != this->currTweening.end()) {
            // percent done!
            double percTime = this->timeElapsed / (*it)->getTweenTime();
            this->amountChange = transition->easeInOut(percTime, transition->SINE);

            // update current value of the TweenParam
            // We don't need setValue() in here bc we are already where we want to be
            (*it)->setCurrChange(amountChange);
        
            if ((*it)->getParam().getKey() == "ALPHA") {
                this->currObject->alpha = (*it)->getCurrVal();
            }
            else if ((*it)->getParam().getKey() == "ROTATION") {
                this->currObject->rotation = (*it)->getCurrVal();    
            }
            else if ((*it)->getParam().getKey() == "SCALE_X") {
                this->currObject->scaleX = (*it)->getCurrVal();
            }
            else if ((*it)->getParam().getKey() == "SCALE_Y") {
                this->currObject->scaleY = (*it)->getCurrVal();
            }
            else if ((*it)->getParam().getKey() == "X") {
                this->currObject->position.x = (*it)->getCurrVal();
            }
            else if ((*it)->getParam().getKey() == "Y") {
                this->currObject->position.y = (*it)->getCurrVal();
            }
            it++;
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
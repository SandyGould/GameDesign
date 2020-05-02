#include "Tween.h"

#include "../events/TweenEvent.h"

#include <algorithm>
#include <iostream>

Tween::Tween(std::weak_ptr<DisplayObject> object) {
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

Tween::Tween(std::weak_ptr<DisplayObject> object, TweenTransitions transition) {
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

Tween::Tween(std::string id, std::weak_ptr<DisplayObject> object){
    this->id = id;
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

Tween::Tween(std::string id, std::weak_ptr<DisplayObject> object, TweenTransitions transition) {
    this->id = id;
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
    this->id = id;
}

std::string Tween::getID(){
    return this->id;
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time) {
    TweenParam* temp = new TweenParam(fieldToAnimate, startVal, endVal, time);
    this->currTweening.push_back(temp);
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time, std::string easeType) {
    TweenParam* temp = new TweenParam(fieldToAnimate, startVal, endVal, time, easeType);
    this->currTweening.push_back(temp);
}

void Tween::update() {
    for (auto it = this->currTweening.begin(); it != this->currTweening.end(); ) {
        // calculate (linear) change manually for now,
        // replace w/ transition function in the future
        
        if(this->timeElapsed > (*it)->getTweenTime()){ 
            it = this->currTweening.erase(it); // remove the param if done w/ tweening
            continue;
        }

        // percent done!
        double percTime = this->timeElapsed / (*it)->getTweenTime();

        if ((*it)->getEaseType() == TweenParam::EASE_IN)
            this->amountChange = transition->easeIn(percTime, transition->SINE);
        else if ((*it)->getEaseType() == TweenParam::EASE_OUT)
            this->amountChange = transition->easeOut(percTime, transition->SINE);
        else if ((*it)->getEaseType() == TweenParam::EASE_IN_OUT)
            this->amountChange = transition->easeInOut(percTime, transition->SINE);
        else if ((*it)->getEaseType() == TweenParam::EASE_OUT_IN)
            this->amountChange = transition->easeOutIn(percTime, transition->SINE);

        // update current value of the TweenParam
        // We don't need setValue() in here bc we are already where we want to be
        (*it)->setCurrChange(amountChange);

        auto object = this->currObject.lock();
        if (!object) {
            it = this->currTweening.erase(it);
            continue;
        }

        if ((*it)->getParam().getKey() == "ALPHA") {
            object->alpha = (*it)->getCurrVal();
        }
        else if ((*it)->getParam().getKey() == "ROTATION") {
            object->rotation = (*it)->getCurrVal();
        }
        else if ((*it)->getParam().getKey() == "SCALE_X") {
            object->scaleX = (*it)->getCurrVal();
        }
        else if ((*it)->getParam().getKey() == "SCALE_Y") {
            object->scaleY = (*it)->getCurrVal();
        }
        else if ((*it)->getParam().getKey() == "X") {
            object->position.x = (*it)->getCurrVal();
        }
        else if ((*it)->getParam().getKey() == "Y") {
            object->position.y = (*it)->getCurrVal();
        }

        EventDispatcher::getInstance().dispatchEvent(new TweenEvent(TweenEvent::TWEEN_UPDATE_EVENT, this));
        it++;
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
    return this->currTweening.empty();
}

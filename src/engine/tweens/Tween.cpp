#include "Tween.h"

#include "../events/TweenEvent.h"

#include <algorithm>
#include <iostream>

Tween::Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object){
    this->id = id;
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

Tween::Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object, const TweenTransitions& transition) {
    this->id = id;
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

std::string Tween::getID(){
    return this->id;
}

void Tween::animate(TweenableParam fieldToAnimate,
                    double startVal, double endVal,
                    double startTime, double duration,
                    EaseType easeType) {
    auto* temp = new TweenParam(fieldToAnimate, startVal, endVal, startTime, duration, easeType);
    this->currTweening.push_back(temp);
}

void Tween::update() {
    for (auto it = this->currTweening.begin(); it != this->currTweening.end(); ) {
        auto param = *it;
        // calculate (linear) change manually for now,
        // replace w/ transition function in the future

        if (this->timeElapsed < param->getStartTime()) {
            it++;
            continue;
        }
        
        if (this->timeElapsed - param->getStartTime() > param->getDuration()) {
            it = this->currTweening.erase(it); // remove the param if done w/ tweening
            delete param;
            continue;
        }

        // percent done!
        double percTime = (this->timeElapsed - param->getStartTime()) / param->getDuration();

        if (param->getEaseType() == EaseType::EASE_IN)
            this->amountChange = transition->easeIn(percTime, transition->SINE);
        else if (param->getEaseType() == EaseType::EASE_OUT)
            this->amountChange = transition->easeOut(percTime, transition->SINE);
        else if (param->getEaseType() == EaseType::EASE_IN_OUT)
            this->amountChange = transition->easeInOut(percTime, transition->SINE);
        else if (param->getEaseType() == EaseType::EASE_OUT_IN)
            this->amountChange = transition->easeOutIn(percTime, transition->SINE);

        // update current value of the TweenParam
        // We don't need setValue() in here bc we are already where we want to be
        param->setCurrChange(amountChange);

        auto object = this->currObject.lock();
        if (!object) {
            it = this->currTweening.erase(it);
            continue;
        }

        if (param->getParam() == TweenableParam::ALPHA) {
            object->alpha = param->getCurrVal();
        }
        else if (param->getParam() == TweenableParam::ROTATION) {
            object->rotation = param->getCurrVal();
        }
        else if (param->getParam() == TweenableParam::SCALE_X) {
            object->scaleX = param->getCurrVal();
        }
        else if (param->getParam() == TweenableParam::SCALE_Y) {
            object->scaleY = param->getCurrVal();
        }
        else if (param->getParam() == TweenableParam::X) {
            object->position.x = param->getCurrVal();
        }
        else if (param->getParam() == TweenableParam::Y) {
            object->position.y = param->getCurrVal();
        }

        EventDispatcher::getInstance().dispatchEvent(new TweenEvent(TweenEvent::TWEEN_UPDATE_EVENT, this));
        it++;
    }
}

void Tween::setValue(TweenableParam param, double value) {
    std::list<TweenParam*>::iterator it;
    for (it = currTweening.begin(); it != currTweening.end(); it++) {
        if ((*it)->getParam() == param) {
            (*it)->setCurrVal(value);
        }
    }
}

bool Tween::isComplete() {
    // tween is complete if no more parameters left to tween
    return this->currTweening.empty();
}

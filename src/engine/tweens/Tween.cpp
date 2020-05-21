#include "Tween.h"

#include "../events/TweenEvent.h"

#include <algorithm>

Tween::Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object) {
    this->id = id;
    this->currObject = object;
    this->amountChange = 0;
    this->timeElapsed = 0;
}

std::string Tween::getID() const {
    return this->id;
}

void Tween::animate(TweenableParam fieldToAnimate,
                    double startVal, double endVal,
                    double startTime, double duration,
                    EaseType easeType) {
    this->currTweening.emplace_back(fieldToAnimate, startVal, endVal, startTime, duration, easeType);
}

void Tween::update() {
    for (auto it = this->currTweening.begin(); it != this->currTweening.end(); ) {
        auto param = *it;
        // calculate (linear) change manually for now,
        // replace w/ transition function in the future

        if (this->timeElapsed < param.getStartTime()) {
            it++;
            continue;
        }
        
        if (this->timeElapsed - param.getStartTime() > param.getDuration()) {
            it = this->currTweening.erase(it); // remove the param if done w/ tweening
            continue;
        }

        // percent done!
        double percTime = (this->timeElapsed - param.getStartTime()) / param.getDuration();

        if (param.getEaseType() == EaseType::EASE_IN) {
            this->amountChange = TweenTransitions::easeIn(percTime, TweenTransition::SINE);
        } else if (param.getEaseType() == EaseType::EASE_OUT) {
            this->amountChange = TweenTransitions::easeOut(percTime, TweenTransition::SINE);
        } else if (param.getEaseType() == EaseType::EASE_IN_OUT) {
            this->amountChange = TweenTransitions::easeInOut(percTime, TweenTransition::SINE);
        } else if (param.getEaseType() == EaseType::EASE_OUT_IN) {
            this->amountChange = TweenTransitions::easeOutIn(percTime, TweenTransition::SINE);
        }

        // update current value of the TweenParam
        // We don't need setValue() in here bc we are already where we want to be
        param.setCurrChange(amountChange);

        auto object = this->currObject.lock();
        if (!object) {
            it = this->currTweening.erase(it);
            continue;
        }

        if (param.getParam() == TweenableParam::ALPHA) {
            object->alpha = param.getCurrVal();
        }
        else if (param.getParam() == TweenableParam::ROTATION) {
            object->rotation = param.getCurrVal();
        }
        else if (param.getParam() == TweenableParam::SCALE_X) {
            object->scaleX = param.getCurrVal();
        }
        else if (param.getParam() == TweenableParam::SCALE_Y) {
            object->scaleY = param.getCurrVal();
        }
        else if (param.getParam() == TweenableParam::X) {
            object->position.x = param.getCurrVal();
        }
        else if (param.getParam() == TweenableParam::Y) {
            object->position.y = param.getCurrVal();
        }

        EventDispatcher::getInstance().dispatchEvent(new TweenEvent(TweenEvent::TWEEN_UPDATE_EVENT, this));
        it++;
    }
}

void Tween::setValue(TweenableParam param, double value) {
    for (auto& curr : currTweening) {
        if (curr.getParam() == param) {
            curr.setCurrVal(value);
        }
    }
}

void Tween::incrementTime() {
    this->timeElapsed += 1;
}

bool Tween::isComplete() const {
    // tween is complete if no more parameters left to tween
    return this->currTweening.empty();
}

#include "TweenJuggler.h"

#include "../events/TweenEvent.h"

#include <iostream>

void TweenJuggler::add(const std::shared_ptr<Tween>& tween) {
    bool found = false;
    for (const auto& t : tweenList) {
        if (t->getID() == tween->getID()) {
            found = true;
        }
    }
    if (!found) {
        tweenList.push_back(tween);
    }
}

void TweenJuggler::nextFrame() {
    for (auto it = this->tweenList.begin(); it != this->tweenList.end(); ) {
        auto tween = *it;
        if (tween->isComplete()) {
            // throw event - tween ending
            EventDispatcher::getInstance().dispatchEvent(new TweenEvent(TweenEvent::TWEEN_COMPLETE_EVENT, tween.get()));
            it = this->tweenList.erase(it);
            continue;
        }

        tween->update();
        tween->incrementTime();
        it++;
    }
}
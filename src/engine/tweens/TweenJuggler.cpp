#include "TweenJuggler.h"

#include <iostream>

void TweenJuggler::add(std::shared_ptr<Tween> tween) {
    bool found = false;
    for (auto t : tweenList) {
        if (t->getID() == tween->getID()) {
            found = true;
        }
    }
    if (!found) {
        tweenList.push_back(tween);
    }
}
// TweenJuggler* TweenJuggler::getInstance() {
//     if (!instance) {
//         instance = new TweenJuggler();
//     }
//     return instance;
// }

void TweenJuggler::nextFrame() {
    for (auto it = this->tweenList.begin(); it != this->tweenList.end(); ) {
        if ((*it)->isComplete()) {
            // throw event - tween ending
            EventDispatcher::getInstance().dispatchEvent(new TweenEvent(TweenEvent::TWEEN_COMPLETE_EVENT, (*it).get()));
            it = this->tweenList.erase(it);
        }
        if (it != this->tweenList.end()) {
            (*it)->update();
            (*it)->incrementTime();
            it++;
        }
    }
}

TweenJuggler* TweenJuggler::instance = nullptr;
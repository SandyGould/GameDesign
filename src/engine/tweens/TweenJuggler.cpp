#include "TweenJuggler.h"

#include <iostream>

TweenJuggler::TweenJuggler() { }

TweenJuggler::~TweenJuggler() {
    tweenList.clear();
}

void TweenJuggler::add(Tween* tween) {
    bool found = false;
    for (auto* t : tweenList) {
        if (t->getID() == tween->getID()) {
            found = true;
        }
    }
    if (!found) {
        tweenList.push_back(tween);
    }
}

void TweenJuggler::nextFrame() {
    std::list<Tween*>::iterator it;
    for (it = this->tweenList.begin(); it != this->tweenList.end(); ) {
        if ((*it)->isComplete()) {
            // throw event - tween ending
            it = this->tweenList.erase(it);
        }
        if (it != this->tweenList.end()) {
            (*it)->update();
            (*it)->incrementTime();
            it++;
        }
    }
}

TweenJuggler* TweenJuggler::instance = 0;
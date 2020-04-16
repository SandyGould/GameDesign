#include "TweenJuggler.h"

TweenJuggler::TweenJuggler() { }

TweenJuggler::~TweenJuggler() {
    tweenList.clear();
}

// TweenJuggler* TweenJuggler::getInstance() {
//     if (!instance) {
//         instance = new TweenJuggler();
//     }
//     return instance;
// }

void TweenJuggler::add(Tween* tween) {
    // throw event - tween starting
    tweenList.push_back(tween);   
}

void TweenJuggler::nextFrame() {
    std::list<Tween*>::iterator it;
    for (it = this->tweenList.begin(); it != this->tweenList.end(); ) {
        if ((*it)->isComplete()) {
            // throw event - tween ending
            this->tweenList.erase(it--);
        }
        else {
            (*it)->update();
            (*it)->incrementTime();
        }
    }
}

TweenJuggler* TweenJuggler::instance = 0;
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

void TweenJuggler::add(std::shared_ptr<Tween> tween) {
    // throw event - tween starting
    tweenList.push_back(tween);   
}

void TweenJuggler::nextFrame() {
    for (auto it = this->tweenList.begin(); it != this->tweenList.end(); ) {
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

TweenJuggler* TweenJuggler::instance = nullptr;
#include "TweenJuggler.h"
#include <iostream>

TweenJuggler::TweenJuggler() {
    // if (created) {
    //     std::cout << "Juggler already instantiated!" << std::endl;
    // }
    // else {
    //     this->instance = this;
    // }
}

TweenJuggler::~TweenJuggler() {
    tweenList.clear();
}

// TweenJuggler* TweenJuggler::getInstance() {
//     return instance;
// }

void TweenJuggler::add(Tween* tween) {
    // throw event - tween starting
    tweenList.push_back(tween);   
}

void TweenJuggler::nextFrame() {
    //std::cout << tweenList.size() << std::endl;
    std::list<Tween*>::iterator it;
    for (it = this->tweenList.begin(); it != this->tweenList.end(); it++) {
        if ((*it)->isComplete()) {
            // throw event - tween ending
            this->tweenList.erase(it--);
        }
        else {
            (*it)->update();
        }
    }
}


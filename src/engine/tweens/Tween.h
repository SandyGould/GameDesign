#pragma once

#include "../DisplayObject.h"
#include "TweenParam.h"
#include "TweenTransitions.h"
#include <list>

// Object representing on Sprite being tweened in some way. Can have multiple TweenParam objects.

class Tween {
public:
    Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object);

    void animate(TweenableParam fieldToAnimate,
                 double startVal, double endVal,
                 double startTime, double duration,
                 EaseType easeType = EaseType::EASE_IN_OUT);
    void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
    void setValue(TweenableParam param, double value);
    void incrementTime();

    [[nodiscard]] std::string getID() const;
    [[nodiscard]] bool isComplete() const;

private:
    std::weak_ptr<DisplayObject> currObject;
    std::list<TweenParam> currTweening;
    double amountChange;
    double timeElapsed;
    std::string id;
};

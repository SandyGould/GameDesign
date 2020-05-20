#ifndef TWEEN_H
#define TWEEN_H

#include "../DisplayObject.h"
#include "TweenParam.h"
#include "TweenTransitions.h"
#include <list>

// Object representing on Sprite being tweened in some way. Can have multiple TweenParam objects.

class Tween { 

    public:
        Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object);
        Tween(const std::string& id, const std::weak_ptr<DisplayObject>& object, const TweenTransitions& transition);

        void animate(TweenableParam fieldToAnimate,
                     double startVal, double endVal,
                     double startTime, double duration,
                     EaseType easeType = EaseType::EASE_IN_OUT);
        void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
        void setValue(TweenableParam param, double value);
        bool isComplete();
        void incrementTime() { this-> timeElapsed += 1; }

        std::string getID();
     
    private:
        std::weak_ptr<DisplayObject> currObject;
        std::list<TweenParam*> currTweening;
        double amountChange;
        double timeElapsed;
        TweenTransitions* transition;
        std::string id;
};

#endif

#ifndef TWEEN_H
#define TWEEN_H

#include "../DisplayObject.h"
#include "TweenParam.h"
#include "TweenTransitions.h"
#include <list>

// Object representing on Sprite being tweened in some way. Can have multiple TweenParam objects.

class Tween { 

    public:
	    Tween(std::shared_ptr<DisplayObject> object);
        Tween(std::shared_ptr<DisplayObject> object, TweenTransitions transition);
        Tween(std::string id, std::shared_ptr<DisplayObject> object);
        Tween(std::string id, std::shared_ptr<DisplayObject> object, TweenTransitions transition);
        ~Tween();
        void animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time);
        void animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time, std::string easeType);
        void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
        void setValue(TweenableParams param, double value);
        bool isComplete();
        void incrementTime() { this-> timeElapsed += 1; }

        std::string getID();
     
    private:
        std::shared_ptr<DisplayObject> currObject;
        std::list<TweenParam*> currTweening;
        double amountChange;
        double timeElapsed;
        TweenTransitions* transition;
        std::string id = "DEFAULT_ID";
};

#endif
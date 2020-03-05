#ifndef TWEEN_H
#define TWEEN_H

#include "../DisplayObject.h"
#include "TweenParam.h"
#include "TweenTransitions.h"
#include <list>

// Object representing on Sprite being tweened in some way. Can have multiple TweenParam objects.

class Tween { 

    public:
	    Tween(DisplayObject* object);
        Tween(DisplayObject* object, TweenTransitions transition);
        ~Tween();
        void animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time);
        void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
        void setValue(TweenableParams param, double value);
        bool isComplete();
     
    private:
        DisplayObject *currObject;
        std::list<TweenParam*> currTweening;
        double amountChange;
        // TweenTransitions* transition;

};

#endif
#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include "TweenableParams.h"

// Object storing information relevant to one parameter being tweened.

class TweenParam { 

public:
	TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time);
    TweenableParams getParam();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
};

#endif
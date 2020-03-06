#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

#include <cmath>

// Class representing different possible transition functions for tweens. 
// You MUST include at least one non-linear Tween transition. 

class TweenTransitions { 

public:
	enum Transition {LINEAR, SINE, EXPO};

	double applyTransition(double percentDone, Transition transition);
	double easeOut(double percentDone, Transition transition);
    double easeIn(double percentDone, Transition transition); // applies a specific transition function, can have more of these for each transition your tweening supports. I will only list one here.
    double easeInOut(double percentDone, Transition transition);
    double easeOutIn(double percentDone, Transition transition);
};

#endif
#pragma once

#include <cmath>

enum class TweenTransition {
    LINEAR,
    SINE,
    EXPO,
};

// Class representing different possible transition functions for tweens. 
// You MUST include at least one non-linear Tween transition. 

class TweenTransitions {
public:
	static double applyTransition(double percentDone, TweenTransition transition);
	static double easeOut(double percentDone, TweenTransition transition);
    static double easeIn(double percentDone, TweenTransition transition); // applies a specific transition function, can have more of these for each transition your tweening supports. I will only list one here.
    static double easeInOut(double percentDone, TweenTransition transition);
    static double easeOutIn(double percentDone, TweenTransition transition);
};

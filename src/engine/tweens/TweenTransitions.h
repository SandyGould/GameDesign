#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

// Class representing different possible transition functions for tweens. 
// You MUST include at least one non-linear Tween transition. 

class TweenTransitions { 

public:
	void applyTransition(double percentDone);
    void easeInOut(double percentDone); // applies a specific transition function, can have more of these for each transition your tweening supports. I will only list one here.
};

#endif
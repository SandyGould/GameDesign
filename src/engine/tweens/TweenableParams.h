#ifndef TWEENABLEPARAMS_H
#define TWEENABLEPARAMS_H

#include <string>

// A list of strings representing the parameters of a Sprite that can be Tweened.

class TweenableParams { 

public:
	enum params { 
		X, Y, SCALE_X = 1, SCALE_Y = 1,
		rotation = 0
	};
};

#endif
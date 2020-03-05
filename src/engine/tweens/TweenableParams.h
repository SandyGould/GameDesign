#ifndef TWEENABLEPARAMS_H
#define TWEENABLEPARAMS_H

#include <string>

// A list of fields representing the parameters of a Sprite that can be Tweened.

class TweenableParams { 
	

	public:
		TweenableParams();
		~TweenableParams();

		// jank C++ enum
		static const TweenableParams SCALE_X;
		static const TweenableParams SCALE_Y;
		static const TweenableParams ALPHA;
		static const TweenableParams ROTATION;
		static const TweenableParams X;
		static const TweenableParams Y;
		
		std::string getKey();

	private:
		std::string key;
		
		// private constructor (for enum)
		TweenableParams(std::string key);
};

#endif
#include "TweenTransitions.h"

constexpr static const auto PI = 3.141592653589793238462643383279502884;

// Linear function
double TweenTransitions::applyTransition(double percentDone, TweenTransition transition){
	return percentDone;
}

double TweenTransitions::easeIn(double percentDone, TweenTransition transition){
	switch(transition){
		case TweenTransition::LINEAR:
			return percentDone;
			break;
		case TweenTransition::SINE:
			return sin(PI/2 * percentDone);
			break;
        case TweenTransition::EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeOut(double percentDone, TweenTransition transition){
	switch(transition){
		case TweenTransition::LINEAR:
			return percentDone;
			break;
		case TweenTransition::SINE:
			return sin((PI/2 * percentDone) + 3*PI/2) + 1;
			break;
		case TweenTransition::EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeInOut(double percentDone, TweenTransition transition){
	switch(transition){
		case TweenTransition::LINEAR:
			return percentDone;
			break;
		case TweenTransition::SINE:
			if(percentDone < 0.5)
				return easeIn(2*percentDone, transition)/2;
			return 0.5 + easeOut(2*percentDone - 1, transition)/2;
            // return percentDone * percentDone * (3 - 2 * percentDone);
			break;
		case TweenTransition::EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeOutIn(double percentDone, TweenTransition transition){
	switch(transition){
		case TweenTransition::LINEAR:
			return percentDone;
			break;
		case TweenTransition::SINE:
			if(percentDone < 0.5)
				return easeOut(2*percentDone, transition)/2;
			return 0.5 + easeIn(2*percentDone - 1, transition)/2;
			break;
        case TweenTransition::EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

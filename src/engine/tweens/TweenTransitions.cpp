#include "TweenTransitions.h"

#include <iostream>

// Linear function
double TweenTransitions::applyTransition(double percentDone, Transition transition){
	return percentDone;
}

double TweenTransitions::easeIn(double percentDone, Transition transition){
	switch(transition){
		case LINEAR:
			return percentDone;
			break;
		case SINE:
			return sin(M_PI/2 * percentDone);
			break;
		case EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeOut(double percentDone, Transition transition){
	switch(transition){
		case LINEAR:
			return percentDone;
			break;
		case SINE:
			return sin((M_PI/2 * percentDone) + 3*M_PI/2) + 1;
			break;
		case EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeInOut(double percentDone, Transition transition){
	switch(transition){
		case LINEAR:
			return percentDone;
			break;
		case SINE:
			if(percentDone < 0.5)
				return easeIn(2*percentDone, transition)/2;
			return 0.5 + easeOut(2*percentDone - 1, transition)/2;
			break;
		case EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}

double TweenTransitions::easeOutIn(double percentDone, Transition transition){
	switch(transition){
		case LINEAR:
			return percentDone;
			break;
		case SINE:
			if(percentDone < 0.5)
				return easeOut(2*percentDone, transition)/2;
			return 0.5 + easeIn(2*percentDone - 1, transition)/2;
			break;
		case EXPO:
			break;
		default:
			return 0.0;
			break;
	}
	return 0.0;
}
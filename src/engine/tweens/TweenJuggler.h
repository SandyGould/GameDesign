#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"

// Singleton class that handles all of the tweens in the game and updates them
// appropriately once per frame.

class TweenJuggler { 

public:
	TweenJuggler();
    void add(Tween tween);
    void nextFrame();  //invoked every frame by Game, calls update() on every Tween and cleans up old / complete Tweens
};

#endif
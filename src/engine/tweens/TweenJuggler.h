#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include "../events/TweenEvent.h"
#include <list>

// Singleton class that handles all of the tweens in the game and updates them
// appropriately once per frame.

class TweenJuggler { 

    public:
    	static TweenJuggler& getInstance() {
            static TweenJuggler instance;
            return instance;
    	}

    	TweenJuggler(TweenJuggler const& other) = delete;
    	void operator=(TweenJuggler const& other) = delete;

	    ~TweenJuggler();
        void add(Tween* tween);
        void nextFrame();  //invoked every frame by Game, calls update() on every Tween and cleans up old / complete Tweens
        std::list<Tween*> tweenList;
        
    private:
        TweenJuggler();
        static TweenJuggler* instance;
};

#endif
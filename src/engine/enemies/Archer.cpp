#include "Archer.h"
#include <cstdlib>

/*
/*
States:
Init 0 
Wait for player 1
Knock arrow 2
Aim 3
Draw arrow back 4
Shoot arrow 5
Cool down 6
Ded 7
*/
/*
// Init
Archer::Archer(){
    //More on this later.
}
//set all the shit for size and stuff.


void Archer::update(std::set<SDL_Scancode> pressedKeys){
    if(this->health ==0){
        this->clean = true
    }

    if(this->clean){
        //cleanup
    }

    if(this->state == 0){
        // Do init stuff
    }

    if(this->state == 1){ //waiting
        if()
        //check for player
        //keep waiting.
        //OR record players coordinates for where to shoot arrow.
    }

    if(this->state == 2){ //prepping
        //make sure player is still in room
        //init an arrow
        //show arrow
        //set next state to 3
    }

    if(this->state == 3){ //
        //turn to look for player (might want to do this for many frames more on that later)
        //set next state to 4
    }

    if(this->state == 4){
        //draw back arrow
    }

    if(this->state == 5){
        //arrow.fire()
    }
    if(this->state == 6){ //waiting
        //do this for between 1 and 3 seconds(will generate some random num between 60 and 180 for num of frames)
    }
}

//attack

//onHit

//draw

//seters

//do things*/
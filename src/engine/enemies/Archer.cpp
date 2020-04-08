#include "Archer.h"
#include <cstdlib>
#include <stdlib.h> 
#include <cmath>
#include <iostream>

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

// Init
Archer::Archer(Player* player): BaseEnemy("Archer", "./resources/assets/Display_Objects/archer.png", player){
    this->state = 0;
}


void Archer::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(this->health ==0){
        this->clean = true;
    }
    if(this->clean){
        //cleanup
    }

    if(this->state == 0){
        this->state = 1; //We have to now move into the next state. :)
    }
    else if(this->state == 1){ //waiting
        //For now we're assuming the player is always in the same room.
        //This works(more later)
        this->state = 2;
    }
    else if(this->state == 2){ //"knock" arrow
        this->arrow = new Arrow(30);
        this->addChild(this->arrow);
        this->actionFrames = 30; //spend half a second adjusting aim.
        this->state = 3;
    }
    else if(this->state == 3){ //aim.
        if(this->actionFrames == 0){
            this->state = 4;
            this->actionFrames=6; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
        }
        else{
            this->actionFrames--;
            if(this->actionFrames%10 == 0){
                
                if((this->goalAngle> this->rotation + M_PI) || (this->goalAngle < this->rotation - M_PI)){
                    this->rotation = this->rotation + (0.75 * abs(this->goalAngle - this->rotation)); //if we're within rot+ pi, rotate +
                }
                else{
                    this->rotation = this->rotation - (0.075 * abs(this->goalAngle - this->rotation)); //if we're not within rot + pi, rotate by -
                }*/
            this->actionFrames--;
        }
    }
    else if(this->state == 4){//draw back arrow
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            arrow->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
        this->state = 5;
    }
    else if(this->state == 5){ //Fire arrow.
        this->arrow->fire(3*M_PI/4);
        this->state = 6;
    }
    else if(this->state == 6){ //cooldown //Works.
        if(coolDownFrames == -1){ //If the cooldown has expired we'll set it to -1
            this->coolDownFrames = generateCoolDown(); 
        }
        else if (coolDownFrames == 0){
            this->coolDownFrames--; //Set to -1.
            this->state = 2; //Switch to next state
        }
        else{
            this->coolDownFrames--; //Wait longer
        }
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

int Archer::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    //return (rand() % 180) + 120;
    return 0;
}

void Archer::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}
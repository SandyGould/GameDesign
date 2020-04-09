#include "MasterArcher.h"
#include <cstdlib>
#include <stdlib.h> 
#include <cmath>
#include <iostream>

static int master_archer_count = 1;
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
MasterArcher::MasterArcher(Player* player): BaseEnemy("MasterArcher" + master_archer_count, "./resources/assets/Display_Objects/master_archer.png", player){
    this->state = 0;
    this->facingRight=true;
    master_archer_count++;
}

void MasterArcher::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
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
        goalAngle = 180;
        if(this->facingRight){
            goalAngle=0;
            arrow->facingRight = true;
        }
        this->addChild(this->arrow);
        ///this->actionFrames = 90; //spend half a second adjusting aim.
        this->state = 3;
    }
    else if(this->state == 3){ //aim.
            //TODO: use a tween to make this look pretty :) 
            this->state = 4;
            this->actionFrames=12; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
            goalAngle = arrow->aim(player);
            arrow->rotation = goalAngle;
    }
    else if(this->state == 4){//draw back arrow
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            arrow->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
    }
    else if(this->state == 5){ //Fire arrow.
        this->arrow->fire(arrow->rotation);
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

int MasterArcher::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    //return (rand() % 180) + 120;
    return 60;
}

void MasterArcher::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}
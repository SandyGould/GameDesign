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
MasterArcher::MasterArcher(Player* player): BaseEnemy("MasterArcher" + master_archer_count, "./resources/assets/Display_Objects/master_archer.png", "", player){
    this->state = 0;
    this->facingRight=true;
    master_archer_count++;
    this->type = "master_archer";
    this->saveType = this->type;
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
        this->arrow1 = new Arrow(35);
        this->arrow2 = new Arrow(35);
        this->arrow3 = new Arrow(35);
        this->addChild(arrow1);
        this->addChild(arrow2);
        this->addChild(arrow3);
        //TODO: configure this to look cool AF
        arrow1->rotation = 15;
        arrow1->position = {5,1};
        arrow2->position = {5,0};
        arrow3->rotation = -15;
        arrow3->position = {5,-1};
        this->state = 3;
    }
    else if(this->state == 3){ //aim.
            //TODO: use a tween to make this look pretty :)
            this->state = 4;
            this->actionFrames=12; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
            arrow2->rotation = arrow2->aim(player);
    }
    else if(this->state == 4){//draw back arrow
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            //arrowParent->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
    }
    else if(this->state == 5){ //Fire arrow.
        double rot = arrow2->rotation;
        arrow1->fire(rot+15);
        arrow2->fire(rot);
        arrow3->fire(rot-15);
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

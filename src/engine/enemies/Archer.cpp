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
Archer::Archer(): BaseEnemy("Archer", "./resources/assets/Display_Objects/archer.png"){
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
        this->actionFrames = 15; 
    }
    else if(this->state == 2){ //knock arrow
        this->arrow = new Arrow();
        this->addChild(this->arrow);
        if(this->actionFrames == 0){ //have we reached the end of the action frames?
            this->actionFrames = 30; //spend half a second adjusting aim.
            this->state = 3;
        }
        else{
            this->actionFrames--;
        }
    }
    else if(this->state == 3){ //aim.
        std::cout<<"State 3\n";
        if(this->actionFrames == 0){
            this->state = 4;
            this->actionFrames=6; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
        }
        else{
            this->actionFrames--;
            //if(actionFrames%10 == 0){
/*                this->player->getHitbox();
                SDL_Point a = player->hitbox_ul;
                SDL_Point b = player->hitbox_lr;
                int x = (int)(a.x + b.x)/2; //finding the median of the x values.
                int y = (int)(a.y + b.y)/2; //Finding the median of the y values.
                target = {x,y};
                a = this->hitbox_ul;
                b = this->hitbox_ul;
                SDL_Point center = {(int)(a.x + b.x)/2, (int)(a.y+b.y)/2};
                goalAngle = atan2(center.y - target.y, center.x-target.x);
            }
                if((this->goalAngle> this->rotation + M_PI) || (this->goalAngle < this->rotation - M_PI)){
                    this->rotation = this->rotation + (0.75 * abs(this->goalAngle - this->rotation)); //if we're within rot+ pi, rotate +
                }
                else{
                    this->rotation = this->rotation - (0.075 * abs(this->goalAngle - this->rotation)); //if we're not within rot + pi, rotate by -
                }
            this->actionFrames--;*/
        }
    }
    else if(this->state == 4){//draw back arrow
        std::cout<<"State 4\n";
        /*arrow->drawBack();
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            this->actionFrames--;
        }*/
        this->state = 5;
    }
    else if(this->state == 5){ //Fire the arrow
        std::cout<<"State 5\n";
        /*SDL_Point position = arrow->hitbox_ul;
        arrow->position = position;
        //this->removeChild(arrow); //arrow is it's own man now.
        arrow->fire();*/
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
    return (rand() % 180) + 120;
}

void Archer::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}
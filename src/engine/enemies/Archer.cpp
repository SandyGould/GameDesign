#include "Archer.h"
#include <cstdlib>
#include <stdlib.h> 
#include <cmath>

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
/*Archer::Archer(){
    //More on this later.
}*/
//set all the shit for size and stuff.


void Archer::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(this->health ==0){
        this->clean = true;
    }
    if(this->clean){
        //cleanup
    }

    if(this->state == 0){
        // Do init stuff
        this->state = 1; //We have to now move into the next state. :)
    }
    else if(this->state == 1){ //waiting
        //For now we're assuming the player is always in the same room.
        this->state = 2;
        this->actionFrames = 15; 
    }
    else if(this->state == 2){ //knock arrow
        arrow = new Arrow();
        this->addChild(arrow);
        if(this->actionFrames == 0){ //have we reached the end of the action frames?
            this->actionFrames = 30; //spend half a second adjusting aim.
            this->state = 3;
        }
        else{
            this->actionFrames--;
        }
    }
    else if(this->state == 3){ //aim.
        if(this->actionFrames == 0){
            this->state = 4;
            this->actionFrames=6; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
        }
        else{
            if(actionFrames%10 == 0){
                this->player->getHitbox();
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
            this->actionFrames--;
        }
    }
    else if(this->state == 4){//draw back arrow
        arrow->drawBack();
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            this->actionFrames--;
        }
    }
    else if(this->state == 5){ //Fire the arrow
       //Find the actual location of the arrow. Set that for the arrow.
       //Drop the arrow from our DOT.
       arrow->fire();
    }
    else if(this->state == 6){ //cooldown
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

        BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
    }
}

int Archer::generateCoolDown(){
    return (rand() % 120) + 60;
}

// void Archer::onCollision(DisplayObject* other){
//     BaseEnemy::
// }

void Archer::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}

#include "Archer.h"
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <iostream>

static int archer_count =1;
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
Archer::Archer(Player* player): BaseEnemy("Archer", "./resources/assets/Display_Objects/archer.png", "", player){
    this->state = 0;
    this->facingRight=true;
    this->type = "archer";
}

void Archer::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    if(this->health ==0){
        this->clean = true;
    }
    if(this->clean){
        this->removeThis();
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
        if(this->facingRight){
            arrow->facingRight = true;
        }
        this->addChild(this->arrow);
        this->actionFrames = 12;
        this->state = 3;
    }
    else if(this->state == 3){//draw back arrow
        if(this->actionFrames ==0){
            this->state =4;
        }
        else{
            arrow->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
    }
    else if(this->state == 4){ //aim.
            //TODO: use a tween to make this look pretty :)
            this->state = 5;
            arrow->rotation = arrow->aim(player);
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

int Archer::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    return (rand() % 180) + 120;
}

void Archer::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}


bool Archer::onCollision(DisplayObject* other){
     if(other->type == "mage_attack" || other->type == "arrow"){
        std::cout<<"ouch\n";
        this->changeHealth(-20);
        other->removeThis();
        return true;
    }
    if(other->type == "rubber_cannonball" || other->type == "cannonball"){
        std::cout<<"Cannoneer\n";
        this->changeHealth(-100);
        return true;
    }
    if(other->type == "poison_bomb"){
        std::cout<<"poison bitch\n";
        this->changeHealth(-1);
        return true;
    }
    if(other->type == "shield"){
        std::cout<<"ow\n";
        this->changeHealth(-35);
    }
    return false;
}

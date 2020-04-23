#include "MonsterKing.h"
#include <cmath>

// Init
// Wait
// Move Select
// Spawn Creeps
// Shoot Ice Projectiles
// Charge
// Bouncing
// Stunned
// Cooldown
// Ded

void MonsterKing::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        // We don't delete this one like the others?
        this->visible = false;
        this->state = -1;
        //
    }

    if(this->state == 0){
        this->state = 1; //We have to now move into the next state. :)
    }
    else if(this->state == 1){ //waiting
        //For now we're assuming the player is always in the same room.
        //This works(more later)
        this->state = 2;
    }
    else if(this->state == 2){ //move select
        this->state = rand() %3 + 3;
    }
    else if(this->state == 3){ // Spawn Creeps
        
    }
    else if(this->state == 4){ // Shoot Ice Projectiles
        
    }
    else if(this->state == 5){ // Charge
        //this leads to bouncing
    }
    else if(this->state == 6){ // Bouncing
        
    }
    else if(this->state == 7){ // Stunned
        if(this->actionFrames == 0){
            this->state =2; //move to select after stun is over.
        }
        else{
            this->actionFrames--;
        }
    }
    else if(this->state == 8){ // Cooldown
        
    }
}
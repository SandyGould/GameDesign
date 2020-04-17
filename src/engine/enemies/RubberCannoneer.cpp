#include "RubberCannoneer.h"

    RubberCannoneer::RubberCannoneer(Player* player) : BaseEnemy("RubberCannoneer", "./resources/assets/Display_Objects/rubber_cannoneer.png", "", player){
        this->type = "rubber_cannoneer";
    }

    void RubberCannoneer::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health==0){
        this->clean = true;
    }

    if(this->clean){
        //Do some cleanup
    }

    if(this->state == 0){
        //init stuff here
    }
    else if(this->state == 1){
        //Waiting lol
        wait = 12;
    }
    else if(this->state == 2){
        if(wait == 12){
            cannonball = new RubberCannonBall(45);
            cannonball->position = {45,0}; //IDK something so it doesn't spawn on top of the cannon lol
        }
        if(wait == 0){
            this->state = 3;
        }
        wait--;
    }
    else if(this->state == 3){
        this->addChild(cannonball);
        this->cannonball->fire(0);
        wait= 45;
        this->state = 4;
    }
    else if(this->state == 4){
        if(wait == 0){
            this->state = 2;
        }
        else{
            wait--;
        }
    }
    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

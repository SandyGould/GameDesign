#include "Knight.h"

Knight::Knight(Player* player): BaseEnemy("knight", "./resources/assets/Display_Objects/knight.png", player){

}

void Knight::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
     /*
     Init
    Wait for player
    Approach player
    Rush
    Attack
    Reset
    Ded
    */   
    if(this->health ==0){
        this->clean = true;
    }
    if(this->clean){
        //cleanup
    }
    if(this->state == 0){
        //init
        this->state=1;
    }
    else if(this->state ==1){
        //waiting
        //TODO: make fixes for this in the beta.
        this->state = 2;
    }
    else if(this->state == 2){
        SDL_Point playerLoc = player->getGlobalPosition();
        int directionX = this->getGlobalPosition().x - playerLoc.x;
        int directionY = this->getGlobalPosition().y - playerLoc.y;
        if(directionX > 0){
            this->position = {this->position.x - 6, this->position.y};
        }
        if(directionX < 0){
            this->position = {this->position.x + 6, this->position.y};
        }
        if(directionY > 0){
            this->position = {this->position.x, this->position.y-6};
        }
        if(directionY < 0){
            this->position = {this->position.x, this->position.y+6};
        }
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionY) < 60 && abs(directionY) < 60){
            this->state = 3;
        }
//        if(near player){this->state = 3}
        //approach player slowly
    }
    else if(this->state == 3){
        //rush player
    }
    else if(this->state == 4){
        //attack
    }
    else if(this->state == 5){
        //rest
    }

}
#include "RoarMonster.h"
#include <iostream>
RoarMonster::RoarMonster(Player* player): BaseEnemy("RoaringMonster","./resources/assets/Display_Objects/roaring_monster.png", "", player){
    this->type="roar_monster";
}

/*
Init
Wait for player
Walk
Sees player
ROAR
Recharge
Ded
*/
void RoarMonster::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
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
    else if(this->state ==2){
        if(actionFrames%30 == 0){
            int x = rand() %90 - 45;
            int y = rand() %90 - 45;
            this->actualPosX = this->position.x;
            this->actualPosY = this->position.y;
            this->xVelocity = x/30;
            this->yVelocity = y/30;
        }
        else{
            this->actualPosX+= xVelocity;
            if(this->actualPosX < 0){
                this->actualPosX = 0;
            }
            if(this->actualPosX > 1200){
                this->actualPosX = 1200;
            }
            this->actualPosY+= yVelocity;
            if(this->actualPosY < 0){
                this->actualPosY = 0;
            }
            if(this->actualPosY > 800){
                this->actualPosY = 800;
            }
        }
        actionFrames= (actionFrames + 29) % 30;
        this->position = {(int)actualPosX, (int)actualPosY};
        /*if(player is in front of me){
            WOAH.
        }*/
    }
    else if(this->state == 3){
        //Player is in my cone of view.
    }
    else if(this->state ==4){
        //ROAR
    }
    else if(this->state == 5){
        //recharge
    }
}

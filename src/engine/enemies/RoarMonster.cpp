#include "RoarMonster.h"
#include <iostream>

static int roar_monster_count = 1;

RoarMonster::RoarMonster(std::shared_ptr<Player> player): BaseEnemy("RoaringMonster" + std::to_string(roar_monster_count),"./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "RoarIdle", player){
    roar_monster_count++;
    this->saveType = "roar_monster";
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
void RoarMonster::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }
    if (Game::instance->paused) {
        return;
    }

    if(this->state == 0){
        //init
        this->state=1;
    }
    else if(this->state ==1){
        if (this->current.animName.compare("RoarIdle") != 0)
            this->play("RoarIdle");
        //waiting
        //TODO: make fixes for this in the beta.
        actionFrames = 60;
        this->state = 2;
    }
    else if(this->state ==2){
        if(actionFrames % 30 == 0){
            int x = rand() %90 - 45;
            int y = rand() %90 - 45;
            this->actualPosX = this->position.x;
            this->actualPosY = this->position.y;
            this->xVelocity = x/30;
            this->yVelocity = y/30;
        }
        else{
            if (this->current.animName.compare("RoarRun") != 0)
                this->play("RoarRun");
            this->actualPosX += xVelocity;
            if(this->actualPosX < 0){
                this->actualPosX = 0;
            }
            if(this->actualPosX > 1200){
                this->actualPosX = 1200;
            }
            this->actualPosY += yVelocity;
            if(this->actualPosY < 0){
                this->actualPosY = 0;
            }
            if(this->actualPosY > 800){
                this->actualPosY = 800;
            }
        }
        actionFrames= (actionFrames + 29) % 30;
        this->position = {(int)actualPosX, (int)actualPosY};
        SDL_Point playerPos = player->getGlobalPosition();
        SDL_Point myPos = this->getGlobalPosition();
        if(playerPos.x - myPos.x < 30 && playerPos.x - myPos.x > -30 && playerPos.y - myPos.y < 30 && playerPos.y - myPos.y > -30){
            this->state = 3;
            this->actionFrames = 15;
        }
    }
    else if(this->state == 3){
        if(this->actionFrames == 0){
            SDL_Point playerPos = player->getGlobalPosition();
            SDL_Point myPos = this->getGlobalPosition();
            if(playerPos.x - myPos.x < 30 && playerPos.x - myPos.x > -30 && playerPos.y - myPos.y < 30 && playerPos.y - myPos.y > -30) {
                this->state = 4;
            }
        }
        else{
            this->actionFrames--;
        }
    }
    else if(this->state ==4){
        this->myAttack = std::make_shared<Roar>();
        this->addChild(myAttack);
        this->state = 5;
        this->actionFrames = 135;
    }

    else if(this->state == 5){
        if(this->actionFrames == 0){
            this->state = 2;
        }
        else{
            this->actionFrames--;
        }
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

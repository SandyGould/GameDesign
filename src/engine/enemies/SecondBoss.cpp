#include "SecondBoss.h"
#include <iostream>
SecondBoss::SecondBoss(Player* player): BaseEnemy("SecondBoss", "./resources/assets/Display_Objects/second_boss/second_boss.png", "", player){
    this->type = "second_boss";
    this->saveType = this->type;
}

void SecondBoss::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        return;
    }

    if(this->state == 0){
        //init
        this->state =1;
    }
    else if(this->state == 1){
        this->state = 2;
    }
    else if(this->state == 2){
        //approach
        this->playerLoc = player->getGlobalPosition();
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 200 && abs(directionY) < 200){
            this->state = 3;
            this->actionFrames = 15;
        }
        else{
            if(directionX > 0){
                this->position = {this->position.x - 2, this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + 2, this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-2};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+2};
            }
            this->actionFrames++;
            if(this->actionFrames==300){
                this->state = 5;
                this->actionFrames = 120;
        }   
        }
    }
    else if(this->state == 3){
        //charge
         if(this->actionFrames == 6){
                SDL_Point playerLoc = player->getGlobalPosition();
            }
            directionX = this->getGlobalPosition().x - playerLoc.x;
            directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 100 && abs(directionY) < 100){
            this->state = 4;
            this->actionFrames = 6;
        }
        else{
            if(directionX > 0){
                this->position = {this->position.x - 8, this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + 8, this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-8};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+8};
            }
            directionX = this->getGlobalPosition().x - playerLoc.x;
            directionY = this->getGlobalPosition().y - playerLoc.y;
            if(this->actionFrames == 0){
              this->state = 2;
            }
            this->actionFrames--;
        }
    }
    else if(this->state == 4){
        this->fire(this->aim(player));
        this->state = 5;
        this->bounces = 8;
    }
    else if(this->state == 5){
        if(bounces==0){
            this->firing = false;
            this->bounces = 8;
            this->actionFrames = 30;
            this->state = 6;
        }
    }
    else if(this->state == 6){
        if(actionFrames == 0){
            this->state = 2;
        }
        this->actionFrames--;
    }

    if(firing){
        this->position.x+=deltaX;
        this->position.y+=deltaY;
    }
    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}



void SecondBoss::fire(double angle){
    deltaX = velocity * cos(angle * PI / 180);
    deltaY = velocity * -sin(angle * PI / 180);
    firing = true;
}

double SecondBoss::aim(DisplayObject* targetSprite){ //Cause a lot of enemies need to aim :)
    //Just finds the angle between the center of the DO given(may be self, may be a Projectile, etc) and the Player
    SDL_Point target = targetSprite->getGlobalPosition();
    //std::cout<<"Target"<<target.x<<","<<target.y<<"\n";
    SDL_Point center = this->getGlobalPosition();
    //std::cout<<"Center"<<center.x<<","<<target.y<<"\n";
    double y = (target.y - center.y);
    double x = (target.x - center.x);
    double goalAngle = atan2(-y, x);
    goalAngle = goalAngle * 180 / PI;
    return goalAngle;
}

//bounes off of literally anything.
bool SecondBoss::onCollision(DisplayObject* other){
    /*bounces--;
    this->deltaX = -this->deltaX * (bounces/8);
    this->deltaY = -this->deltaY * (bounces/8);
    return false;*/
    return true;
}
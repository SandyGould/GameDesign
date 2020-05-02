#include "KingdomKing.h"
#include <iostream>
/*
 He will be given all of the abilities of the kingdom enemies, (Master Archer, melee, rubber projectiles, mage)
 */


/*
States:
0 init
1 wait
2 choose attack
3 melee
4 arrows
5 rubber projectile
6 magic attack
*/

KingdomKing::KingdomKing(std::shared_ptr<Player> player) : BaseEnemy("kingdom_king", "./resources/assets/Animated_Sprites/Enemies/king.png", "./resources/assets/Animated_Sprites/Enemies/king.xml", "King", player){

}


void KingdomKing::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }
    //std::cout<<"State:"<<this->state<<"\n";
    if(this->state == 0){
        //init
        this->state = 1;
    }
    else if(this->state ==1){
        this->state = 2;
    }
    else if(this->state == 2){ //Choose your attack.
        int randInt = rand() % 4;
        std::cout<<"State 2 "<<randInt<<"\n";
        if(randInt == 0){
            this->state = 3; //melee
        }
        else if(randInt == 1){
            this->state = 6; //arrow
        }
        else if(randInt ==2){
            this->actionFrames = 10;
            this->state = 10; //I am the attack
        }
        else
        {
            this->actionFrames = 271;
            this->state = 12;
        }
    }
    //===================================== Melee ================================== //
    else if(this->state == 3){
        std::cout<<"State3\n";
        this->playerLoc = player->getGlobalPosition();
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 100 && abs(directionY) < 100){
            this->state = 4;
            this->actionFrames = 15;
        }
        else{
            if(directionX > 0){
                this->position = {this->position.x - static_cast<int>(2*this->speed), this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + static_cast<int>(2*this->speed), this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-static_cast<int>(2*this->speed)};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+static_cast<int>(2*this->speed)};
            }
            this->actionFrames++;
            if(this->actionFrames==300){
                this->state = 14;
                this->actionFrames = rand()%90;
        }   
        }
    }
    else if(this->state == 4){
        if(this->actionFrames == 6){
                SDL_Point playerLoc = player->getGlobalPosition();
            }
            directionX = this->getGlobalPosition().x - playerLoc.x;
            directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 50 && abs(directionY) < 50){
            this->state = 5;
            this->actionFrames = 6;
        }
        else{
            if(directionX > 0){
                this->position = {this->position.x - static_cast<int>(8*this->speed), this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + static_cast<int>(8*this->speed), this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-static_cast<int>(8*this->speed)};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+static_cast<int>(8*this->speed)};
            }
            directionX = this->getGlobalPosition().x - playerLoc.x;
            directionY = this->getGlobalPosition().y - playerLoc.y;
            if(this->actionFrames == 0){
              this->state = 2;
            }
            this->actionFrames--;
        }
    }
    else if(this->state == 5){
        if(this->actionFrames == 0){
            this->actionFrames = 120;
            this->state = 14;
        }
        if(this->actionFrames >3){
            if(directionX > 0){
                this->position = {this->position.x - static_cast<int>(5*this->speed), this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + static_cast<int>(5*this->speed), this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-static_cast<int>(5*this->speed)};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+static_cast<int>(5*this->speed)};
            }
        } else{
            if(directionX > 0){
                this->position = {this->position.x + static_cast<int>(5*this->speed), this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x - static_cast<int>(5*this->speed), this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y+static_cast<int>(5*this->speed)};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y-static_cast<int>(5*this->speed)};
            }
        }
        this->actionFrames--;
    }
    //========================= Shooting an arrow =============================//
    else if(this->state == 6){ //"knock" arrow
            std::cout<<"State6\n";
            this->arrow = std::make_shared<Arrow>(30);
            if(this->facingRight){
                arrow->facingRight = true;
            }
            this->addChild(this->arrow);
            this->actionFrames = 12;
            this->state = 7;
        }
        else if(this->state == 7){//draw back arrow
            std::cout<<"State7\n";
            if(this->actionFrames ==0){
                this->state =8;
            }
            else{
                arrow->drawBack(); //Slowly draw back for a few frames :)
                this->actionFrames--;
            }
        }
        else if(this->state == 8){ //aim.
                //TODO: use a tween to make this look pretty :)
                std::cout<<"State8\n";
                this->state = 9;
                arrow->rotation = arrow->aim(player);
        }
        else if(this->state == 9){ //Fire arrow.
            std::cout<<"State9\n";
            this->arrow->fire(arrow->rotation);
            this->state = 14;
            this->actionFrames = rand() % 60;
        }
        // ========================== Shooting himself as a projectile ============================//
        else if(this->state == 10){
            if(actionFrames == 0){
                this->state = 11;
            }
            else{
                actionFrames--;
            }
        }
        else if(this->state == 11){
            this->fire(this->aim(player));
            this->actionFrames = 180;
            this->state = 14; //We will either quit doing stuff after 3s or when we stop bouncing.
        }
        //============================== Mage Attack ===============================//
        else if(this->state == 12){
            this->actionFrames--;
            if(this->actionFrames==240){
                this->mageAttack = std::make_shared<MageAttack>();
                this->addChild(mageAttack);
                mageAttack->visible=true;
                this->state = 13;
            }
        }
        else if(this->state == 13){
            this->actionFrames--;
            if(this->actionFrames == 0){
                this->mageAttack->target = this->mageAttack->aim(player);
                this->mageAttack->fire();
                this->actionFrames = 60;
                this->state = 14;
            }
        }
        //==================================== Cooldown ===================================//
        else if(this->state == 14){
            if(actionFrames == 0){
                if(this->firing){
                    this->firing = false;
                    this->actionFrames = 60;
                }
                else{
                    this->state =2;
                }
            }
            else{
                actionFrames--;
            }
        }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}



void KingdomKing::fire(double angle){
    deltaX = velocity * cos(angle * PI / 180);
    deltaY = velocity * -sin(angle * PI / 180);
    firing = true;
}



double KingdomKing::aim(std::shared_ptr<DisplayObject> targetSprite){ //Cause a lot of enemies need to aim :)
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

void KingdomKing::reflect() {
    this->deltaX = -deltaX;
    this->deltaY = -deltaY;
}

bool KingdomKing::onCollision(std::shared_ptr<DisplayObject> other){
    return false;
}

#include "Ogre.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

/*
States:
Init 0
Wait for player 1
Select Attack Type 2
Knock arrow 3
Draw arrow back 4
Shoot arrow 5
Approach Player 6
Melee Attack 7
Cool down 8
Dead 9
*/

// Init
Ogre::Ogre(std::shared_ptr<Player> player): BaseEnemy("ogre", "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "OgreIdle", player){
    this->state = 0;
    this->facingRight=true;
    this->type = "ogre";
    this->saveType = this->type;
    this->actionFrames = 12;
    this->arrow = nullptr;
}

void Ogre::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }
    if (Game::instance->paused) {
        return;
    }

    if(this->state == 0) {
        this->state = 1; //We have to now move into the next state. :)
    }

    else if(this->state == 1) { //waiting
        //For now we're assuming the player is always in the same room.
        //This works(more later)
        this->state = 2;
    }

    else if (this->state == 2) {
        if (rand() >= RAND_MAX/2) {
            this->state = 3;
        } else {
            this->state = 6;
        }
    }

    else if(this->state == 3){ //"knock" arrow
        this->arrow = std::make_shared<Arrow>(30);
        arrow->facingRight = this->facingRight;
        this->addChild(this->arrow);
        this->actionFrames = 12;
        this->state = 4;
    }
    else if(this->state == 4){//draw back arrow
        if(this->actionFrames == 0){
            arrow->rotation = arrow->aim(player);
            this->state = 5;
        }
        else {
            arrow->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
    }
    else if (this->state == 5) { //Fire arrow.
        this->arrow->fire(arrow->rotation);
        this->state = 8;
    }

    else if (this->state == 6) {
        SDL_Point playerLoc = player->getGlobalPosition();
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if (this->current.animName.compare("OgreRun") != 0)
            this->play("OgreRun");
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
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 60 && abs(directionY) < 60){
            this->state = 7;
            this->actionFrames = 6;
        }
    }

    else if (this->state == 7) {
        if(this->actionFrames == 0){
            this->actionFrames = 120;
            this->state = 8;
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

    else if(this->state == 8) { //cooldown //Works.
        if (this->current.animName.compare("OgreIdle") != 0)
            this->play("OgreIdle");
        if (coolDownFrames == -1) { //If the cooldown has expired we'll set it to -1
            this->coolDownFrames = generateCoolDown();
        }
        else if (coolDownFrames == 0) {
            this->coolDownFrames--; //Set to -1.
            this->state = 2; //Switch to next state
        }
        else {
            this->coolDownFrames--; //Wait longer
        }
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

int Ogre::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    return (rand() % 180) + 120;
}

bool Ogre::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
     if(other == arrow && arrow->firing == false){
         return true;
     }
    return BaseEnemy::onCollision(other, direction1, direction2);
}

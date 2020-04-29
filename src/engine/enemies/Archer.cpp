#include "Archer.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

static int archer_count = 1;
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
Archer::Archer(std::shared_ptr<Player> player): BaseEnemy("Archer" + std::to_string(archer_count), "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "ArcherIdle", player){
    this->state = 0;
    this->facingRight=true;
    this->saveType = "archer";
    this->actionFrames = 12;
    this->arrow = nullptr;
    archer_count++;
}

Archer::Archer(std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName): BaseEnemy("Archer" + std::to_string(archer_count), filepath, xml, animName, player){

}

void Archer::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        return;
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
        this->arrow = std::make_shared<Arrow>(10);
        if(this->facingRight){
            arrow->facingRight = true;
        }
        this->addChild(this->arrow);
        this->actionFrames = 26;
        this->state = 3;
    }
    else if(this->state == 3){//draw back arrow
        if(this->actionFrames ==0){
            this->state = 4;
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

bool Archer::onCollision(std::shared_ptr<DisplayObject> other){
     if(other == arrow && arrow->firing == false){
         return true;
     }
    return BaseEnemy::onCollision(other);
}

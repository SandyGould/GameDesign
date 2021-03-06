#include "MasterArcher.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

static int master_archer_count = 1;
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
// TODO: Shouldn't this dude inherit from Archer instead?
MasterArcher::MasterArcher(std::shared_ptr<Player> player) : BaseEnemy("MasterArcher" + std::to_string(master_archer_count), "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "MArcherIdle", player){
    this->state = 0;
    this->facingRight=true;
    master_archer_count++;
    this->saveType = "MasterArcher";
}

void MasterArcher::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        // We don't delete this one like the others?
        this->visible = false;
        this->state = -1;
        this->player->numOpponents -= 1;
    }
    if (Game::instance->paused) {
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
        /*this->arrows.emplace_back(new Arrow(35));
        this->arrow1 = arrows.back();
        this->arrows.emplace_back(new Arrow(35));
        this->arrow2 = arrows.back();
        this->arrows.emplace_back(new Arrow(35));
        this->arrow3 = arrows.back();*/
        this->arrow1 = std::make_shared<Arrow>(3);
        this->arrow2 = std::make_shared<Arrow>(3);
        this->arrow3 = std::make_shared<Arrow>(3);
        arrows.emplace_back(arrow1);
        arrows.emplace_back(arrow2);
        arrows.emplace_back(arrow3);
        this->addChild(arrow1);
        this->addChild(arrow2);
        this->addChild(arrow3);
        // std::cout<<this->children.size();
        //TODO: configure this to look cool AF
        arrow1->rotation = 15;
        arrow1->position = {5,1};
        arrow2->position = {5,0};
        arrow3->rotation = -15;
        arrow3->position = {5,-1};
        this->state = 3;
    }
    else if(this->state == 3){ //aim.
            //TODO: use a tween to make this look pretty :)
            this->state = 4;
            this->actionFrames=22; //SET THIS TO THE NUMBER OF FRAMES FOR DRAWING BACK ANIMATION(if we get one)
            arrow2->rotation = arrow2->aim(player);
    }
    else if(this->state == 4){//draw back arrow
        if(this->actionFrames ==0){
            this->state =5;
        }
        else{
            //arrowParent->drawBack(); //Slowly draw back for a few frames :)
            this->actionFrames--;
        }
    }
    else if(this->state == 5){ //Fire arrow.
        double rot = arrow2->rotation;
        arrows.pop_back();
        arrows.pop_back();
        arrows.pop_back();
        arrow1->fire(rot+15);
        arrow2->fire(rot);
        arrow3->fire(rot-15);
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

int MasterArcher::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    //return (rand() % 180) + 120;
    return 180;
}

bool MasterArcher::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    if(arrows.size() == 3){
        if(other == arrows.at(0)|| other==arrows.at(1) || other==arrows.at(2)){
            return true;
        }
    }
    return BaseEnemy::onCollision(other, direction1, direction2);
}

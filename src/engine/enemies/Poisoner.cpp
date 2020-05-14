#include "Poisoner.h"

static int poisoner_count = 1;

Poisoner::Poisoner(std::shared_ptr<Player> player) : BaseEnemy("poisoner" + std::to_string(poisoner_count), "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "PoisonerIdle", player){
    poisoner_count++;
    this->saveType="poisoner";
}

/*
Wait for player
Walk around room
Place poison
Walk away
Recharge
Ded
*/
void Poisoner::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
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
        this->state = 1;
    }
    else if(this->state == 1){
        //wait
        this->actionFrames = 120;
        this->state = 2;
    }
    else if(this->state == 2){
        if(this->actionFrames%30 == 0){
            int x = rand() %2 - 1;
            int y = rand() %2 - 1;
            if(x == 0 && y ==0){
                y = 1;
            }
            this->xVelocity = 5 * x;
            this->yVelocity = 5 * y;
        }
        int newX = (this->position.x + xVelocity) % 1200;
        int newY = (this->position.y + yVelocity) % 800;
        if(newX < 0){
            newX = 0;
        }
        if(newY < 0){
            newY = 0;
        }
        this->position= {newX, newY};

        this->actionFrames--;
        if(this->actionFrames == 0){
            this->state=3;
            this->actionFrames=6;
        }
    }
    else if(this->state == 3){
        auto bomb = std::make_shared<PoisonBomb>();
        parent->addChild(bomb);
        bomb->position = this->position;
        this->actionFrames--;
        //place poison
        if(this->actionFrames==0){
            this->state = 4;
            this->actionFrames = 60;
        }
        if(this->position.x > 600){
            this->xVelocity = -4;
        }
        else{
            this->xVelocity = 4;
        }
        if(this->position.y > 400){
            this->yVelocity = -4;
        }
        else{
            this->yVelocity = 4;
        }
    }
    else if(this->state == 4){
        if (this->current.animName.compare("PoisonerRun") != 0)
            this->play("PoisonerRun");
        this->actionFrames--;
        if(this->actionFrames == 0){
            this->state = 5;
            this->actionFrames = 120;
        }
        this->position = {this->position.x + xVelocity, this->position.y + yVelocity};
    }
    else if(this->state == 5){
        if (this->current.animName.compare("PoisonerIdle") != 0)
            this->play("PoisonerIdle");
        if(this->actionFrames ==0){
            this->actionFrames = 120;
            this->state = 2;
        }
        else{
            actionFrames--;
        }
    }
    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

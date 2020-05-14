#include "Knight.h"
#include <iostream>

static int knight_count = 1;

Knight::Knight(std::shared_ptr<Player> player) : Knight("knight" + std::to_string(knight_count), player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "KnightIdle"){
    knight_count++;
}

Knight::Knight(std::string id, std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName) : BaseEnemy(id, filepath, xml, animName, player){
    this->type = "knight";
    this->saveType = this->type;
}

void Knight::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
     /*
     Init
    Wait for player
    Approach player
    Rush
    Attack
    Reset
    Ded
    */
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }
    if (Game::instance->paused) {
        return;
    }

    this->cooldown--;
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
        this->playerLoc = player->getGlobalPosition();
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 100 && abs(directionY) < 100){
            this->state = 3;
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
                this->state = 5;
                this->actionFrames = 120;
            }
        }
    }
    else if(this->state == 3){
        if(this->actionFrames == 6){
                SDL_Point playerLoc = player->getGlobalPosition();
            }
            directionX = this->getGlobalPosition().x - playerLoc.x;
            directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 50 && abs(directionY) < 50){
            this->state = 4;
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
    else if(this->state == 4){
        if(this->actionFrames == 0){
            this->actionFrames = 120;
            this->state =5;
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
    else if(this->state == 5){ //complete
        if(this->actionFrames==0){
            this->state = 2;
        }
        this->actionFrames--;
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);

}

bool Knight::onCollision(std::shared_ptr<DisplayObject> other) {
    if (other == this->player) {
        if (this->cooldown <= 0) {
            this->player->changeHealth(-10);
            this->cooldown = 30;
        }
        return true;
    }
    return BaseEnemy::onCollision(other);
}

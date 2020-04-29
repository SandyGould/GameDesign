#include "MonsterKing.h"
#include <cmath>

static int mking_count = 1;
// Init
// Wait
// Move Select
// Spawn Creeps
// Shoot Ice Projectiles
// Approach Player
// Charge
// Stunned
// Cooldown
// Ded

MonsterKing::MonsterKing(std::shared_ptr<Player> player) : BaseEnemy("monsterKing", "./resources/assets/Animated_Sprites/Enemies/monsterKing.png", "./resources/assets/Animated_Sprites/Enemies/monsterKing.xml", "MKingIdle", player) {
    this->state = 0;
    this->health = 100;
    this->facingRight=true;
    this->type = "monsterKing";
    this->saveType = this->type;
    this->stunFrames = 90;
}

void MonsterKing::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        // We don't delete this one like the others?
        this->visible = false;
        this->state = -1;
        //
    }

    if(this->state == 0){
        this->play("MKingIdle");
        this->ready = 301;
        this->state = 1;
    }
    else if(this->state == 1){ //waiting
        //For now we're assuming the player is always in the same room.
        //This works(more later)
        this->state = 2;
    }
    else if(this->state == 2){ //move select
        if (this->current.animName.compare("MKingIdle") != 0)
            this->play("MKingIdle");
        this->state = rand() %3 + 3;
        this->maxWalkFrames = 380;
    }
    else if(this->state == 3){ // Spawn Creeps
        this->state = 4;
    }
    else if (this->state == 4) { // Shoot Ice Projectiles
        if (this->ready == 201) {
            this->iceAttack = std::make_shared<IceAttack>();
     		this->addChild(iceAttack);
            iceAttack->visible =false;
        } else if (this->ready == 140) {
            iceAttack->visible=true;
        } else if (this->ready == 0) {
            this->iceAttack->target = this->iceAttack->aim(player);
            this->iceAttack->fire();
            this->ready = 201;
            this->state = 5;

        }
        this->ready--;
    }
    else if(this->state == 5){ // Approach
        this->maxWalkFrames--;
        SDL_Point playerLoc = player->getGlobalPosition();
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if (this->current.animName.compare("MKingWalk") != 0)
            this->play("MKingWalk");
        if(directionX > 0){
            this->position = {this->position.x - 1, this->position.y};
        }
        if(directionX < 0){
            this->position = {this->position.x + 1, this->position.y};
        }
        if(directionY > 0){
            this->position = {this->position.x, this->position.y-1};
        }
        if(directionY < 0){
            this->position = {this->position.x, this->position.y+1};
        }
        directionX = this->getGlobalPosition().x - playerLoc.x;
        directionY = this->getGlobalPosition().y - playerLoc.y;
        if(abs(directionX) < 120 && abs(directionY) < 120){
            this->state = 6;
            this->rushFrames = 32;
        }
        if (maxWalkFrames == 0) {
            this->state = 2;
        }
    }
    else if (this->state == 6) { // Charge
        if(this->rushFrames == 0){
            this->rushFrames = 32;
            this->state = 8;
        }
        if(this->rushFrames >3){
            if(directionX > 0){
                this->position = {this->position.x - 5, this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x + 5, this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y-5};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y+5};
            }
        } else{
            if(directionX > 0){
                this->position = {this->position.x + 5, this->position.y};
            }
            if(directionX < 0){
                this->position = {this->position.x - 5, this->position.y};
            }
            if(directionY > 0){
                this->position = {this->position.x, this->position.y+5};
            }
            if(directionY < 0){
                this->position = {this->position.x, this->position.y-5};
            }
        }
        this->rushFrames--;
    }
    else if(this->state == 7){ // Stunned
        if (this->current.animName.compare("MKingIdle") != 0)
            this->play("MKingIdle");
        if(this->stunFrames == 0){
            this->stunFrames = 90;
            this->state = 2; //move to select after stun is over.
        }
        else{
            this->stunFrames--;
        }
    }
    else if(this->state == 8){ // Cooldown
        if (this->current.animName.compare("MKingIdle") != 0)
            this->play("MKingIdle");
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

int MonsterKing::generateCoolDown(){ //returns a number of frames that will be at least 2 seconds, but at most 5
    return (rand() % 180) + 120;
}

void MonsterKing::draw(AffineTransform& at){
    BaseEnemy::draw(at);
}


bool MonsterKing::onCollision(std::shared_ptr<DisplayObject> other){
    if(other == this->iceAttack && iceAttack->firing == false){
        return true;
    }
    return BaseEnemy::onCollision(other);
}

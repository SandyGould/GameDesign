#include "Cannoneer.h"

static int cannoneer_count = 1;

Cannoneer::Cannoneer(std::shared_ptr<Player> player) : BaseEnemy("Cannoneer" + std::to_string(cannoneer_count), "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "CannoneerIdle", player){
    cannoneer_count++;
    this->type = "cannoneer";
    cannon= std::make_shared<Sprite>("cannon", "./resources/assets/Display_Objects/cannon.png");
    this->addChild(cannon);
    this->saveType = this->type;
    cannon->position={-100,20};
}


/*Init
Wait for player
Load Cannon
Shoot Cannon
Wait for refresh (Random time between 1 and 3 seconds.
Ded
*/
void Cannoneer::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if (Game::instance->paused) {
        return;
    }
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }

    if(this->state == 0){
        cannon->scaleHeight(this->height*1.5);
        cannon->scaleWidth(this->width*1.5);
        this->state = 1;
    }
    else if(this->state == 1){
        this->state =2;
        wait = 12;
    }
    else if(this->state == 2){
        if(wait == 12){
            cannonball = std::make_shared<Projectile>("Cannonball", "./resources/assets/Display_Objects/cannonball.png", 45);
            cannonball->scaleX = 2;
            cannonball->scaleY = 2;
            cannonball->position = {45,0}; //IDK something so it doesn't spawn on top of the cannon lol
        }
        if(wait == 0){
            this->state = 3;
        }
        wait--;
    }
    else if(this->state == 3){
        this->addChild(cannonball);
        this->cannonball->fire(180);
        wait= 45;
        this->state = 4;
    }
    else if(this->state == 4){
        if(wait == 0){
            this->state = 2;
        }
        else{
            wait--;
        }
    }
    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

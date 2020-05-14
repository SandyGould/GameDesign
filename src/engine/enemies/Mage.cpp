#include "Mage.h"

#include <iostream>

#define ATTACK_CHARGE 120
#define ATTACK_COOLDOWN 221

static int mage_count = 1;

Mage::Mage(std::shared_ptr<Player> player) : Mage("mage" + std::to_string(mage_count), player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "MageIdle") {
    mage_count++;
}

Mage::Mage(std::string id, std::shared_ptr<Player> player, std::string filepath, std::string xml, std::string animName): BaseEnemy(id, filepath, xml, animName, player){
    hasCollision = true;
    this->saveType = "mage";
    this->mageAttack = nullptr;
}

/*
Init
Wait for player
Aim
Fire Attack
Reload
Ded*/
void Mage::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons){
    if(this->health <= 0) {
        this->removeThis();
        this->player->numOpponents -= 1;
        return;
    }
    if (Game::instance->paused) {
        return;
    }

    if(this->state == 0){
        this->ready = 301;
        this->state = 1;
    }
    else if(this->state ==1){
        //wait for player
        this->state = 2;
    }
    else if(this->state == 2){
        if(this->ready == ATTACK_COOLDOWN){
            this->mageAttack = std::make_shared<MageAttack>();
            this->mageAttack->position = {-6, -6};
     		this->addChild(mageAttack);
            mageAttack->visible =false;
        }
        this->ready--;
        if(this->ready==ATTACK_CHARGE){
            mageAttack->visible=true;
            this->state = 3;
        }
    }
    else if(this->state == 3){
        this->ready--;
        if(this->ready == 0){
            this->mageAttack->target = this->mageAttack->aim(player);
            this->mageAttack->fire();
            this->ready = ATTACK_COOLDOWN;
            this->state = 2;
        }
    }

    BaseEnemy::update(pressedKeys, joystickState, pressedButtons);
}

bool Mage::onCollision(std::shared_ptr<DisplayObject> other){
    if(other == this->mageAttack && this->mageAttack->firing == false){
        return true;
    }
    return BaseEnemy::onCollision(other);
}

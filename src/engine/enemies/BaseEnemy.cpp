#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(std::string id, std::string filepath, Player* player) : Sprite(id, filepath, Game::renderer){
    hasCollision=true;
    this->player = player;
}

void BaseEnemy::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    Sprite::update(pressedKeys,joystickState,pressedButtons);
}

void  BaseEnemy::draw(AffineTransform& at){
    Sprite::draw(at);
}

double BaseEnemy::aim(DisplayObject* projectile){ //Cause a lot of enemies need to aim :)
    //Just finds the angle between the center of the DO given(may be self, may be a Projectile, etc) and the Player
    SDL_Point target = player->getGlobalPosition();
    SDL_Point center = this->getGlobalPosition();
    double goalAngle = atan2(center.y - target.y, center.x-target.x);
    return goalAngle;
}
//void BaseEnemy::onCollision(DisplayObject* other)


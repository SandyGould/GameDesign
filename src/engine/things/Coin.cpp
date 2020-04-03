#include "Coin.h"
#include "../events/Collision.h"
#include "../events/Event.h"

int coin_id_counter = 1;

Coin::Coin() : Sprite("coin_"+std::to_string(coin_id_counter) , "./resources/assets/Display_Objects/Planet.png"){
    ++coin_id_counter;
    type = "coin";
    hasCollision = true;
}

void Coin::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons){
    Sprite::update(pressedKeys, joystickState, pressedButtons);
}

void Coin::draw(AffineTransform& at){
    Sprite::draw(at);
}

void Coin::handleEvent(Event* e){
    if (e->getType() == "collision"){
        if(((Collision*) e)->getDOID() == this->id){
            this->visible = false;
        }
    }
}

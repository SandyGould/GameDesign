#include "Coin.h"

Coin::Coin() : Sprite("temp", "./resources/solarSystem/Planet.png"){

}

void Coin::update(set<SDL_Scancode> pressedKeys){
    Sprite::update(pressedKeys);
}

void Coin::draw(AffineTransform& at){
    Sprite::draw(at);
}

void Coin::handleEvent(Event* e){
    
}
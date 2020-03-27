#include "Collision.h"

#include <string>

Collision::Collision(std::string type, std::string DO_id) : Event(type){
    this->DO_id = DO_id;
}

std::string Collision::getDOID(){
    return DO_id;
}
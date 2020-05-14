#include "Roar.h"

static int roar_count = 1;

Roar::Roar() : Sprite("roar" + std::to_string(roar_count), ""){
    roar_count++;
    this->type = "roar";
}
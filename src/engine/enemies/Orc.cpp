#include "Orc.h"

Orc::Orc(std::shared_ptr<Player> player) : Knight(player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml"){
    this->play("OrcIdle");
}

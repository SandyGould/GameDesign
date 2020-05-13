#include "Orc.h"

static int orc_count = 1;

Orc::Orc(std::shared_ptr<Player> player) : Knight(player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "OrcIdle"){
    this->id = "orc" + std::to_string(orc_count);
    orc_count++;
}

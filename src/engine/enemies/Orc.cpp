#include "Orc.h"

static int orc_count = 1;

Orc::Orc(std::shared_ptr<Player> player) : Knight("Orc" + std::to_string(orc_count), player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "OrcIdle"){
    orc_count++;
    this->type = "orc";
}

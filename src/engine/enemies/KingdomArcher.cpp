#include "KingdomArcher.h"

static int kingdom_archer_count = 1;

KingdomArcher::KingdomArcher(std::shared_ptr<Player> player) : Archer("KingdomArcher" + std::to_string(kingdom_archer_count), player, "./resources/assets/Animated_Sprites/Enemies/enemies.png", "./resources/assets/Animated_Sprites/Enemies/enemies.xml", "KArcherIdle"){
    kingdom_archer_count++;
}

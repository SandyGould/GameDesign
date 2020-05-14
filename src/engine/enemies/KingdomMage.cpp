#include "KingdomMage.h"

static int kingdom_mage_count = 1;

KingdomMage::KingdomMage(std::shared_ptr<Player> player): Mage("KingdomMage" + std::to_string(kingdom_mage_count), player,"./resources/assets/Animated_Sprites/Enemies/enemies.png","./resources/assets/Animated_Sprites/Enemies/enemies.xml", "KMageIdle"){
    kingdom_mage_count++;
}

#include "Orc.h"

Orc::Orc(std::shared_ptr<Player> player) :Knight(player, "./resources/assets/Display_Objects/Orc.png", ""){
    this->saveType = "Orc";
}

#ifndef KINGDOMARCHER_H
#define KINGDOMARCHER_H

#include "Archer.h"

class KingdomArcher : public Archer{
    public:
        KingdomArcher(std::shared_ptr<Player> player);
};

#endif
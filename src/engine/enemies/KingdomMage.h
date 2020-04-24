#ifndef KINGDOMMAGE_H
#define KINGDOMMAGE_H

#include "Mage.h"

class KingdomMage : public Mage{
    public:
        KingdomMage(std::shared_ptr<Player> player);

};

#endif

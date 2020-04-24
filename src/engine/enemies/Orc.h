#ifndef ORC_H
#define ORC_H
#include "Knight.h"

class Orc : public Knight{
    public:
        Orc(std::shared_ptr<Player> player);
};

#endif
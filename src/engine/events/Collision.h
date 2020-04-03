#ifndef COLLISION_H
#define COLLISION_H

#include "Event.h"
#include "EventDispatcher.h"

#include <string>

class Collision : public Event{
public:
    Collision(std::string type, std::string DO_id);

    std::string getDOID();

private:
    std::string DO_id;
};

#endif
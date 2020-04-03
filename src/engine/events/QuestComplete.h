#ifndef QUESTCOMPLETE_H
#define QUESTCOMPLETE_H

#include "Event.h"
#include "EventDispatcher.h"

#include <string>

class QuestComplete : public Event{
public:
    QuestComplete(std::string type, std::string quest_id);

    std::string getQuestID();

private:
    std::string quest_id;
};

#endif
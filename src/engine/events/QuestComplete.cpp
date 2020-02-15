#include "QuestComplete.h"

#include <string>

QuestComplete::QuestComplete(std::string type, EventDispatcher* source, std::string quest_id) : Event(type, source){
    this->quest_id = quest_id;
}

std::string QuestComplete::getQuestID(){
    return quest_id;
}
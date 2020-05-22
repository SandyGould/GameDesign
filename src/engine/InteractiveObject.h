#pragma once

#include "DisplayObject.h"
#include "Game.h"

class InteractiveObject : public DisplayObject {
public:
    InteractiveObject(std::string id, std::string filepath, SDL_Renderer *r = Game::renderer);
};

#include "InteractiveObject.h"

// Has a special exclusion in CollisionSystem to detect collisions even when stationary
InteractiveObject::InteractiveObject(std::string id, std::string filepath, SDL_Renderer* r)
    : DisplayObject(id, filepath, r) {
    this->type = "InteractiveObject";
}

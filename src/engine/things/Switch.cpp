#include "Switch.h"

Switch::Switch(const std::string& id, SDL_Renderer* r): EnvironmentObject(id, "./resources/Rebound/area3_res/assets/switch_off.png"){
    this->type = "Switch";
    this->state_on = "./resources/Rebound/area3_res/assets/switch_on.png";
    this->state_off = "./resources/Rebound/area3_res/assets/switch_off.png";
    this->renderer = r;
}

bool Switch::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
	if(other->type == "player" && !state){
        state = true;
        this->imgPath = this->state_on;
        loadTexture(imgPath);

        for (const auto& child : this->children) {
            child->visible = !child->visible;
        }
		return true;
    }
    else if(state){
        return true; // Allow players to walk on the switch even after it has been turned on
    }
	return false;
}

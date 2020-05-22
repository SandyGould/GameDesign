#include "Switch.h"

#include "Player.h"

Switch::Switch(const std::string& id, SDL_Renderer* r) : InteractiveObject(id, "./resources/Rebound/area3_res/assets/switch_off.png"){
    this->type = "Switch";
    this->renderer = r;
}

bool Switch::onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) {
    auto player = std::dynamic_pointer_cast<Player>(other);
	if (player && player->interacting) {
        this->state = !this->state;
        this->imgPath = this->image_states[this->state];
        loadTexture(this->imgPath);

        for (const auto& child : this->children) {
            child->visible = !child->visible;
        }
    }
	return true;
}

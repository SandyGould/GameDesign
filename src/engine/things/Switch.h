#pragma once

#include "../CollisionSystem.h"
#include "../EnvironmentObject.h"

class Switch : public EnvironmentObject {

public:
	explicit Switch(const std::string& id, SDL_Renderer* r = Game::renderer);

    bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2) override;

private:
    std::array<std::string, 2> image_states{"./resources/Rebound/area3_res/assets/switch_off.png",
                                            "./resources/Rebound/area3_res/assets/switch_on.png"};
    bool state = false;
};

#pragma once

#include "../../engine/Camera.h"
#include "../../engine/CollisionSystem.h"
#include "../../engine/Game.h"
#include "../../engine/Scene.h"
#include "../../engine/things/Player.h"

class LoadSceneDemo : public Game {

public:
    LoadSceneDemo();
    ~LoadSceneDemo() override;

private:
    CollisionSystem* collisionSystem;

    void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform &at) override;
    void draw_post() override;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Player> player;
};

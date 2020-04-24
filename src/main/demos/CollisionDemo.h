#pragma once

#include "../../engine/Camera.h"
#include "../../engine/CollisionSystem.h"
#include "../../engine/Game.h"
#include "../../engine/Scene.h"
#include "../../engine/things/Coin.h"

class CollisionDemo : public Game {

public:
    CollisionDemo();
    ~CollisionDemo() override;

private:
    CollisionSystem* collisionSystem;

    void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform &at) override;
    void draw_post() override;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<DisplayObject> parentObj;
    std::shared_ptr<Coin> child1;
    std::shared_ptr<Coin> child2;
    std::shared_ptr<Player> player;
};

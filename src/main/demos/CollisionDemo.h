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

    Camera* camera;
    Scene* scene;
    DisplayObject* parentObj;
    Coin* child1;
    Coin* child2;
    Player* player;
};

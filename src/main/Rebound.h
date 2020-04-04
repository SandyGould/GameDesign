#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"
#include "../engine/enemies/Archer.h"
#include "../engine/things/Player.h"
#include "../engine/QuestManager.h"

class Rebound : public Game {

public:
	Rebound();
	~Rebound() override;

private:
    CollisionSystem* collisionSystem;
    Player* player;
    Archer* mage;
    DisplayObject* allSprites;
    void update(unordered_set<SDL_Scancode> pressedKeys, jState joystickState, unordered_set<Uint8> pressedButtons) override;
};

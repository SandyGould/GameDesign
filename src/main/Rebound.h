#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Player.h"
#include "../engine/things/Shield.h"
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"

class Rebound : public Game {

public:
	Rebound();
	~Rebound() override;

private:
    CollisionSystem* collisionSystem;
	Player* player;
	Shield* shield;

	DisplayObject* allSprites;

	QuestManager* questManager;

	std::unordered_set<SDL_Scancode>* history;

	// DisplayObject* character;
	Scene* scene;
	Scene* scene2;

	void updateHistory(std::unordered_set<SDL_Scancode> pressedKeys);
	bool checkDoubleTaps(SDL_Scancode key);

    void update(unordered_set<SDL_Scancode> pressedKeys, jState joystickState, unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;
};

#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/things/Player.h"
#include "../engine/things/Shield.h"
#include "../engine/enemies/Mage.h"
#include "../engine/enemies/MageAttack.h"
#include "../engine/enemies/Archer.h"
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"
#include "../engine/enemies/MasterArcher.h"
#include "../engine/enemies/Cannoneer.h"
#include "../engine/enemies/RubberCannoneer.h"
#include "../engine/enemies/RoarMonster.h"
#include "../engine/enemies/Knight.h"
#include "../engine/enemies/KingdomArcher.h"
#include "../engine/enemies/KingdomMage.h"
#include "../engine/enemies/Orc.h"
#include "../engine/enemies/Ogre.h"
#include "../engine/enemies/Poisoner.h"
#include "../engine/enemies/Arrow.h"
#include "../engine/enemies/SecondBoss.h"

class Rebound : public Game {

public:
	Rebound();
	~Rebound() override;

private:
    CollisionSystem* collisionSystem;
	Player* player;
	Mage* mage;
    Archer* archer;
	MageAttack* mageAttack;
	MasterArcher* masterArcher;
	RoarMonster* roarMonster;
	Cannoneer* cannoneer;
	Knight* knight;
	RubberCannoneer* rubberCannoneer;
	KingdomArcher* kingdomArcher;
	Poisoner* poisoner;
	Orc* orc;
	Ogre* ogre;
	KingdomMage* kingdomMage;
	DisplayObject* allSprites;
	Arrow* arrow;
	SecondBoss* secondBoss;
	QuestManager* questManager;

	DisplayObject* character;
	Scene* scene;
	Scene* scene2;

    void update(unordered_set<SDL_Scancode> pressedKeys, jState joystickState, unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;
};

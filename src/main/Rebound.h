#pragma once

#include "../engine/Game.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/things/Player.h"
#include "../engine/things/Shield.h"
#include "../engine/things/Chest.h"
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
#include "../engine/enemies/MonsterKing.h"
#include "../engine/enemies/KingdomKing.h"
#include "../engine/enemies/Poisoner.h"
#include "../engine/enemies/Arrow.h"
#include "../engine/enemies/SecondBoss.h"

class Rebound : public Game {

public:
	Rebound();
	~Rebound() override;

private:
    CollisionSystem* collisionSystem;
	std::shared_ptr<Player> player;
	std::shared_ptr<Chest> chest;
	std::shared_ptr<Mage> mage;
    std::shared_ptr<Archer> archer;
	std::shared_ptr<MageAttack> mageAttack;
	std::shared_ptr<MasterArcher> masterArcher;
	std::shared_ptr<RoarMonster> roarMonster;
	std::shared_ptr<Cannoneer> cannoneer;
	std::shared_ptr<Knight> knight;
	std::shared_ptr<RubberCannoneer> rubberCannoneer;
	std::shared_ptr<KingdomArcher> kingdomArcher;
	std::shared_ptr<Poisoner> poisoner;
	std::shared_ptr<Orc> orc;
	std::shared_ptr<Ogre> ogre;
	std::shared_ptr<MonsterKing> mKing;
	std::shared_ptr<KingdomKing> king;
	std::shared_ptr<KingdomMage> kingdomMage;
	std::shared_ptr<DisplayObject> allSprites;
	std::shared_ptr<Arrow> arrow;
	std::shared_ptr<SecondBoss> secondBoss;
	std::shared_ptr<QuestManager> questManager;

	std::shared_ptr<DisplayObject> character;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Scene> scene2;

    void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;
};

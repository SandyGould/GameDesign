#include "Rebound.h"
#include <iostream>

using namespace std;

Rebound::Rebound() : Game(1200, 800) {
	cout << "Launching Rebound" << endl;
    instance = this;

    this->collisionSystem = new CollisionSystem();

	allSprites = new DisplayObject("allSprites");

	questManager = new QuestManager();

	// move that point to the middle
	allSprites->position = {200, 100};
	container->addChild(allSprites);
	player = new Player();
	player->position = {0, 0};
	player->width = 110;
	player->height = 80;
	player->pivot = {50, 50};
	player->play("Idle");
	player->shield->visible = true;
	allSprites->addChild(player);

	/*mage = new Mage(player);
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);

    archer = new Archer(player);
    archer-> position = {200,200};
    archer->height = 80;
    archer->width = 70;

    allSprites->addChild(archer);*/

	// ogre = new Ogre(player);
    // ogre-> position = {200,200};
    // ogre->height = 160;
    // ogre->width = 150;
	// ogre->play("OgreIdle");
	//
    // allSprites->addChild(ogre);

	mKing = new MonsterKing(player);
    mKing->position = {300,200};
    mKing->height = 160;
    mKing->width = 150;

    allSprites->addChild(mKing);

	/*masterArcher = new MasterArcher(player);
    masterArcher-> position = {500,500};
    masterArcher->height = 80;
    masterArcher->width = 70;

    allSprites->addChild(masterArcher);


	orc = new Orc(player);
	orc->position = {450,450};
	orc->height = 80;
	orc->width = 70;

	allSprites->addChild(orc);

	poisoner = new Poisoner(player);
	poisoner->position = {40,160};
	poisoner->height = 80;
	poisoner->width = 70;

	allSprites->addChild(poisoner);
	roarMonster = new RoarMonster(player);
	roarMonster-> position = {100, 100};
	roarMonster->height = 80;
	roarMonster->width = 70;

	allSprites->addChild(roarMonster);

	knight = new Knight(player);
	knight->position = {200,400};
	knight->height = 80;
	knight->width = 70;

	allSprites->addChild(knight);

	cannoneer = new Cannoneer(player);
	cannoneer->position = {500,100};
	cannoneer->height = 80;
	cannoneer->width = 70;

	allSprites->addChild(cannoneer);

	rubberCannoneer = new RubberCannoneer(player);
	rubberCannoneer->position = {600, 200};
	rubberCannoneer->height=80;
	rubberCannoneer->width=70;

	allSprites->addChild(rubberCannoneer);

	kingdomArcher = new KingdomArcher(player);
	kingdomArcher->position = {400,200};
	kingdomArcher->height= 80;
	kingdomArcher->width=80;

	allSprites->addChild(kingdomArcher);


	kingdomMage = new KingdomMage(player);
	kingdomMage->position = {350,350};
	kingdomMage->height = 80;
	kingdomMage->width = 70;

	allSprites->addChild(kingdomMage);*/

	// secondBoss = new SecondBoss(player);
	// secondBoss->position = {600,600};
	// secondBoss->height = 100;
	// secondBoss->width = 100;

	// allSprites->addChild(secondBoss);

	collisionSystem->watchForCollisions("player", "arrow");
	collisionSystem->watchForCollisions("player", "poison_bomb");
	collisionSystem->watchForCollisions("player", "knight");
	collisionSystem->watchForCollisions("player", "mage_attack");
	collisionSystem->watchForCollisions("player", "cannonball");
	collisionSystem->watchForCollisions("player", "rubber_cannonball");

	collisionSystem->watchForCollisions("shield", "arrow");
	collisionSystem->watchForCollisions("shield", "mage_attack");
	collisionSystem->watchForCollisions("shield", "cannonball");
	collisionSystem->watchForCollisions("shield", "rubber_cannonball");
	collisionSystem->watchForCollisions("shield", "enemy");
	collisionSystem->watchForCollisions("shield", "knight");
	collisionSystem->watchForCollisions("shield", "ogre");

	collisionSystem->watchForCollisions("enemy", "arrow");
	collisionSystem->watchForCollisions("enemy", "mage_attack");
	collisionSystem->watchForCollisions("enemy", "cannonball");
	collisionSystem->watchForCollisions("enemy", "rubber_cannonball");
	collisionSystem->watchForCollisions("enemy", "poison_bomb");

	collisionSystem->watchForCollisions("knight", "arrow");
	collisionSystem->watchForCollisions("knight", "mage_attack");
	collisionSystem->watchForCollisions("knight", "cannonball");
	collisionSystem->watchForCollisions("knight", "rubber_cannonball");
	collisionSystem->watchForCollisions("knight", "poison_bomb");

	collisionSystem->watchForCollisions("ogre", "arrow");
	collisionSystem->watchForCollisions("ogre", "mage_attack");
	collisionSystem->watchForCollisions("ogre", "cannonball");
	collisionSystem->watchForCollisions("ogre", "rubber_cannonball");
	collisionSystem->watchForCollisions("ogre", "poison_bomb");
}

Rebound::~Rebound() {
}

void Rebound::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    this->collisionSystem->update();

	Game::update(pressedKeys, joystickState, pressedButtons);
}

void Rebound::draw(AffineTransform& at) {
	Game::draw(at);
}

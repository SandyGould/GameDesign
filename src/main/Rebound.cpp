#include "Rebound.h"
#include "../engine/events/DisplayTreeChangeEvent.h"
#include <iostream>

using namespace std;

Rebound::Rebound() : Game(1200, 800) {
	cout << "Launching Rebound" << endl;
    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

	allSprites = new DisplayObject("allSprites");

	questManager = new QuestManager();

	// move that point to the middle
	allSprites->position = {200, 100};
	instance->addChild(allSprites);

	player = new Player();
	player->position = {0, 0};
	player->width = 110;
	player->height = 80;
	player->pivot = {50, 50};
	player->play("Idle");
	allSprites->addChild(player);


	mage = new Mage(player);
	mage->position = {400, 400};
	mage->height = 80;
	mage->width = 70;

	allSprites->addChild(mage);

    archer = new Archer(player);
    archer-> position = {200,200};
    archer->height = 80;
    archer->width = 70;

    allSprites->addChild(archer);

	masterArcher = new MasterArcher(player);
    masterArcher-> position = {500,500};
    masterArcher->height = 80;
    masterArcher->width = 70;

    allSprites->addChild(masterArcher);

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
	
	poisoner = new Poisoner(player);
	poisoner->position = {750,750};
	poisoner->height = 80;
	poisoner->width = 70;

	allSprites->addChild(poisoner);

	orc = new Orc(player);
	orc->position = {150, 150};
	orc->height = 80;
	orc->width = 70;

	allSprites->addChild(orc);

	kingdomMage = new KingdomMage(player);
	kingdomMage->position = {350,350};
	kingdomMage->height = 80;
	kingdomMage->width = 70;

	allSprites->addChild(kingdomMage);
}

Rebound::~Rebound() {
}

void Rebound::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    this->collisionSystem->update();

	updateHistory(pressedKeys);

	Game::update(pressedKeys, joystickState, pressedButtons);
}

void Rebound::draw(AffineTransform& at) {
	Game::draw(at);
}

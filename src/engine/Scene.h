#pragma once

#include "things/Player.h"
#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "Sprite.h"
#include "events/Event.h"
#include "events/EventListener.h"

#include "EnvironmentObject.h"
#include "WalkOnObject.h"
#include "HitObject.h"
/*
#include "enemies/Arrow.h"
#include "enemies/MageAttack.h"
#include "enemies/PoisonBomb.h"
#include "enemies/RubberCannonBall.h"
#include "enemies/Archer.h"
#include "enemies/Cannoneer.h"
#include "enemies/Knight.h"
#include "enemies/Mage.h"
#include "enemies/MasterArcher.h"
#include "enemies/Ogre.h"
#include "enemies/Poisoner.h"
#include "enemies/RoarMonster.h"
#include "enemies/RubberCannoneer.h"
#include "enemies/SecondBoss.h"
*/
#include "enemies/Archer.h"
#include "enemies/BaseEnemy.h"
#include "enemies/Cannoneer.h"
#include "enemies/KingdomArcher.h"
#include "enemies/KingdomMage.h"
#include "enemies/Knight.h"
#include "enemies/Mage.h"
#include "enemies/MasterArcher.h"
#include "enemies/Ogre.h"
#include "enemies/Orc.h"
#include "enemies/Poisoner.h"
#include "enemies/RoarMonster.h"
#include "enemies/RubberCannoneer.h"
#include "enemies/SecondBoss.h"

#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObject {

public:
	Scene();
	Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Player> player);
	explicit Scene(std::string id);
	~Scene() override = default;

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void loadScene_Editor(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &Layer, std::shared_ptr<DisplayObject> dObject);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;

	std::shared_ptr<DisplayObject> setBasicInfo(std::shared_ptr<DisplayObject> d_obj, json j);
  /*
	DisplayObject* generateDO(json j);
	AnimatedSprite* generateAS(json j);
	Sprite* generateSprite(json j);
	Arrow* generateArrow(json j);
	MageAttack* generateMageAttack(json j);
	PoisonBomb* generatePoisonBomb(json j);
	RubberCannonBall* generateRubberCannonBall(json j);
	Archer* generateArcher(json j);
	Cannoneer* generateCannoneer(json j);
	Knight* generateKnight(json j);
	Mage* generateMage(json j);
	MasterArcher* generateMasterArcher(json j);
	Ogre* generateOgre(json j);
	Poisoner* generatePoisoner(json j);
	RoarMonster* generateRoarMonster(json j);
	RubberCannoneer* generateRubberCannoneer(json j);
	SecondBoss* generateSecondBoss(json j);

	Player* p = NULL;
  */

	// for scene transitions
	bool keepScene = false;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;

	// pointers to previous and next scenes
	std::shared_ptr<Scene> prevScene = NULL;
	std::shared_ptr<Scene> nextScene = NULL;

	// define SDL points for advancing to next scene, or going back to previous scene
	SDL_Point goForward = {1200,200};
	SDL_Point goBack = {0,200};
	// define when you could go forward and backward
	std::string forward_coord = std::string("x"); // 1 for x
	std::string forward_comp = std::string(">"); // 2 for greater than
	std::string back_coord = std::string("x");
	std::string back_comp = std::string("<"); // 1 for less than

	// starting camera positions
	SDL_Point camEntrancePivot = {200,100};
	SDL_Point camEntrancePosition = {200,100};
	// starting player position
	SDL_Point playerEntrancePos = {50,250};

	// ending camera positions
	SDL_Point camExitPivot = {800,100};
	SDL_Point camExitPosition = {200,100};
	
	// starting player position
	SDL_Point playerExitPos = {1150,250};
	
	std::string scenePath = "";

private:
	std::shared_ptr<DisplayObject> root;

};

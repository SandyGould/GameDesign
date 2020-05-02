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
#include "things/Switch.h"
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
#include "enemies/MonsterKing.h"
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
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;

	// pointers to previous and next scenes
	std::shared_ptr<Scene> prevScene = NULL;
	std::shared_ptr<Scene> nextScene = NULL;

	// define SDL points for advancing to next scene, or going back to previous scene
	SDL_Point goForward = {1000,1000};
	SDL_Point goBack = {0,0};
	
	// conditions for going on to the next scene
	std::string forward_coord = std::string("x"); // i.e, go on to next scene when the player x is greater than goForward.x
	std::string forward_comp = std::string(">"); 
	
	// conditions for going back to the previous scene
	std::string back_coord = std::string("x");
	std::string back_comp = std::string("<"); 

	// starting camera positions
	SDL_Point camEntrancePivot = {0,0};
	SDL_Point camEntrancePosition = {0,0};
	
	// starting player position
	SDL_Point playerEntrancePos = {0,0};

	// ending camera positions
	SDL_Point camExitPivot = {0,0};
	SDL_Point camExitPosition = {0,0};
	
	// starting player position
	SDL_Point playerExitPos = {0,0};
	
	std::string scenePath = "";

	// setting camera limits
	int camTopLimit;
	int camBottomLimit;
	int camRightLimit;
	int camLeftLimit;
	

private:
	std::shared_ptr<DisplayObject> root;

};

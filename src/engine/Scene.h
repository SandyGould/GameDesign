#pragma once

#include "DisplayObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
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
#include "Camera.h"
#include "events/Event.h"
#include "events/EventListener.h"


#include "json.hpp"

#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;

class Scene : public DisplayObject, public EventListener {

public:
	Scene();
	explicit Scene(std::string id);
	// ~Scene() override;

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void loadScene_Editor(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &Layer, DisplayObject* dObject);

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;
	void setCameraRef(Camera* camera);

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

	// for scene transitions
	void handleEvent(Event* e) override;
	bool keepScene = false;
	
private:
	DisplayObject* root;

};

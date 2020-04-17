#pragma once

#include "things/Player.h"
#include "DisplayObject.h"
#include "AnimatedSprite.h"

#include "EnvironmentObject.h"
#include "WalkOnObject.h"
#include "HitObject.h"

#include "Sprite.h"
#include "Camera.h"


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
	Scene(Camera* camera, Player* player);
	explicit Scene(std::string id);
	// ~Scene() override;

	/* Load scene from a file */
	void loadScene(std::string sceneFilePath);
	void saveScene(std::string sceneName);
	void addToJSON(nlohmann::json &Layer, DisplayObject* dObject);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

	DisplayObject* setBasicInfo(DisplayObject* d_obj, json j);

	// for scene transitions
	bool keepScene = false;
	Player* player;
	Camera* camera;

private:
	DisplayObject* root;

};

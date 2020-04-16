#include "Rooms.h"

#include "../engine/events/KeyDownEvent.h"
#include "../engine/events/MouseDownEvent.h"
#include "../engine/events/TweenEvent.h"
#include "../engine/tweens/TweenParam.h"
#include "../engine/tweens/TweenJuggler.h"
#include "../engine/events/NewSceneEvent.h"
#include "../engine/events/DisplayTreeChangeEvent.h"


#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

Rooms::Rooms() : Game(600, 500) {
	
	instance = this;

	camera = new Camera();

	// load and prep camera
	camera->setTopLimit(0);
	camera->setLeftLimit(200);
	camera->setRightLimit(810);
    camera->setBottomLimit(0);
	// move that point to the middle
	camera->position = {200, 100};
	camera->pivot = {200, 100};

	instance->addChild(camera);

	// load and prep scene 1
	room = 1;
	scene = new Scene();
	scene->loadScene("./resources/Rebound/area1/area1map.json");
	scene->setCameraRef(camera);
	camera->addChild(scene);
	// set types of children (for collisions)
	scene->getChild("L0")->getChild("stone")->type = "env_object";
	scene->getChild("L0")->getChild("sign")->type = "env_object";
	scene->getChild("L0")->getChild("top_trees")->type = "env_object";
	scene->getChild("L0")->getChild("bottom_trees")->type = "env_object";

	// load and prep scene 2
	scene2 = new Scene();
	scene2->loadScene("./resources/Rebound/area2/area2map.json");
	//scene2->setCameraRef(camera);
	//camera->addChild(scene2);
	// set types of children (for collisions)
	scene2->getChild("L0")->getChild("structure1")->type = "env_object";
	scene2->getChild("L0")->getChild("structure2")->type = "env_object";
	scene2->getChild("L0")->getChild("barrel")->type = "env_object";

	// load and prep player
	player = new Player();
	// player = new AnimatedSprite("girl", "./resources/assets/Spritesheets/Girl/Girl.png", "./resources/assets/Spritesheets/Girl/Girl.xml");
	player->position = {50, 250};
	player->width = player->height = 50;
	player->pivot = {50, 50};
	//player->type = "player";
	scene->addChild(player);

	// start text box
	start_text_box = new TextBox("start_text", "Welcome to Rebound!\n\nPress any key to continue");
	start_text_box->addTextPanel("To move, press up, down, left, or right\n\nPress any key to continue");
	start_text_box->position = {300, 300};
	start_text_box->alpha = 0;
	instance->addChild(start_text_box);

	// menu
	selection_menu_base = new SelectionMenuBase();
	selection_menu_base->width = 600;
	selection_menu_base->height = 500;
	instance->addChild(selection_menu_base);

	selection_resume_option = new SelectionMenuOption(SelectionMenuOption::RESUME, "Resume");
	selection_resume_option->width = 200;
	selection_resume_option->height = 50;
	selection_resume_option->position = {200, 200};
	selection_resume_option->alpha = 0;
	selection_menu_base->addChild(selection_resume_option);

	selection_quit_option = new SelectionMenuOption(SelectionMenuOption::QUIT, "Quit");
	selection_quit_option->width = 200;
	selection_quit_option->height = 50;
	selection_quit_option->position = {200, 300};
	selection_quit_option->alpha = 0;
	selection_menu_base->addChild(selection_quit_option);

	EventDispatcher::getInstance().addEventListener(this->selection_menu_base, KeyDownEvent::ESC_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_resume_option, MouseDownEvent::MOUSE_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_quit_option, MouseDownEvent::MOUSE_DOWN_EVENT);

	// health bar
	health = new StatBar("Health", 255, 0, 0);
	health->position = {50,460};
	instance->addChild(health);

	// tween stuff
	player_tween = new Tween("player_tween", player);

    player_tween->animate(TweenableParams::SCALE_X, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::SCALE_Y, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::ALPHA, 0, 255, 100);

    TweenJuggler::getInstance().add(player_tween);
    EventDispatcher::getInstance().addEventListener(this->start_text_box, TweenEvent::TWEEN_COMPLETE_EVENT);
	EventDispatcher::getInstance().addEventListener(this->scene, NewSceneEvent::OUT_SCENE_EVENT);
	EventDispatcher::getInstance().addEventListener(this->scene2, NewSceneEvent::IN_SCENE_EVENT);


	// create collision system
	this->collisionSystem = new CollisionSystem();
	EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);
	// set collisions between player and all environmental objects
	this->collisionSystem->watchForCollisions("player", "env_object");
}

Rooms::~Rooms() {
	//delete camera;
	//delete scene;
	//delete health;
	//delete player;
	//delete scene2;
}


void Rooms::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
	this->collisionSystem->update();

	std::cout << "x" << std::endl;
	std::cout << player->position.x << std::endl;
	std::cout << "y" << std::endl;
	std::cout << player->position.y << std::endl;


	// scene 1 controls
	if (room == 1) {
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			if (player->position.x < 1230 || (player->position.y < 350 && player->position.y > 175)) {
				player->position.x += 2;
			}
		}
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        	if (player->position.x > 30) {
            	player->position.x -= 2;
        	}
		}
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			player->position.y += 2;
		}
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			if (player->position.y > 30) {
				player->position.y -= 2;
			}
		}
		if (player->position.x > 1231) {
			//EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::OUT_SCENE_EVENT));
			player->addChild(scene2);
			camera->removeImmediateChild(scene);
			scene2->setCameraRef(camera);
			// set new parameters for next scene
			camera->addChild(scene2);
			camera->setRightLimit(810);
			//EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::IN_SCENE_EVENT));
			player->position = {50, 250};
			this->room = 2;
		}
	}
	if (room == 2) {
		if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
			if (player->position.x < 1230 || (player->position.y < 350 && player->position.y > 175)) {
				player->position.x += 2;
			}
		}
		if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        	if (player->position.x > 30) {
            	player->position.x -= 2;
        	}
		}
		if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			player->position.y += 2;
		}
		if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
			if (player->position.y > 30) {
				player->position.y -= 2;
			}
		}
	}


	// menu controls
	if (pressedKeys.find(SDL_SCANCODE_ESCAPE) != pressedKeys.end()) {
		if(!esc_prepressed)
	 		EventDispatcher::getInstance().dispatchEvent(new Event(KeyDownEvent::ESC_DOWN_EVENT));
	 	esc_prepressed = true;
	} else {
		esc_prepressed = false;
	}

    TweenJuggler::getInstance().nextFrame();
	Game::update(pressedKeys, joystickState, pressedButtons);
	camera->follow(player->position.x, player->position.y);
}

void Rooms::draw(AffineTransform& at) {
	Game::draw(at);
}
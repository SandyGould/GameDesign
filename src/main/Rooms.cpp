#include "Rooms.h"

#include "../engine/events/KeyDownEvent.h"
#include "../engine/events/MouseDownEvent.h"
#include "../engine/events/TweenEvent.h"
#include "../engine/tweens/TweenParam.h"
#include "../engine/tweens/TweenJuggler.h"
#include "../engine/events/NewSceneEvent.h"
#include "../engine/SceneManager.h"


#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

Rooms::Rooms() : Game(600, 500) {
	instance = this;

    // create collision system
    this->collisionSystem = std::make_unique<CollisionSystem>();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "enemy");
    this->collisionSystem->watchForCollisions("enemy", "EnvironmentObject");


	camera = std::make_shared<Camera>();

	// load and prep camera
	camera->setTopLimit(0);
	camera->setLeftLimit(0); //200
	camera->setRightLimit(810); //810
    camera->setBottomLimit(0); //0
	// move that point to the middle

	container->addChild(camera);

	// load and prep player
	player = std::make_shared<Player>();
	player->position = {50, 250};
	// player->width = 110;
	// player->height = 80;
	player->pivot = {50, 50};
	//player->type = "player";

	// start text box
	start_text_box = std::make_shared<TextBox>("start_text", "Welcome to Rebound!\n\nPress any key to continue");
	start_text_box->addTextPanel("To move, press up, down, left, or right\n\nPress any key to continue");
	start_text_box->position = {300, 300};
	start_text_box->alpha = 0;
	container->addChild(start_text_box);

	// menu
	selection_menu_base = std::make_shared<SelectionMenuBase>();
	selection_menu_base->width = 600;
	selection_menu_base->height = 500;
	container->addChild(selection_menu_base);

	selection_resume_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::RESUME, "Resume");
	selection_resume_option->width = 200;
	selection_resume_option->height = 50;
	selection_resume_option->position = {200, 200};
	selection_resume_option->alpha = 0;
	selection_menu_base->addChild(selection_resume_option);

	selection_quit_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::QUIT, "Quit");
	selection_quit_option->width = 200;
	selection_quit_option->height = 50;
	selection_quit_option->position = {200, 300};
	selection_quit_option->alpha = 0;
	selection_menu_base->addChild(selection_quit_option);

	EventDispatcher::getInstance().addEventListener(this->selection_menu_base.get(), KeyDownEvent::ESC_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_resume_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_quit_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);

	// health bar
	health = std::make_shared<StatBar>("Health", 255, 0, 0, player);
	health->position = {50,460};
	container->addChild(health);

	// tween stuff
	player_tween = std::make_shared<Tween>("player_tween", player);

    player_tween->animate(TweenableParams::SCALE_X, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::SCALE_Y, 5.0, 1.0, 100);
	player_tween->animate(TweenableParams::ALPHA, 0, 255, 100);

    TweenJuggler::getInstance().add(player_tween);
    EventDispatcher::getInstance().addEventListener(this->start_text_box.get(), TweenEvent::TWEEN_COMPLETE_EVENT);
	
	
	this->sceneManager = std::make_shared<SceneManager>(camera, player);
	// load the entire first area
	this->sceneManager->loadAllAreas(4);
	// load first scene
	this->sceneManager->loadFirstScene();
}

void Rooms::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		player->position.x += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        player->position.x -= 2;
    }
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
			player->position.y += 2;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		player->position.y -= 2;
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
    
	// update scene if criteria for changing scene are met
	this->sceneManager->updateScene();
	health->updateHealth();
	Game::update(pressedKeys, joystickState, pressedButtons);
	player->slowed = false;
    this->collisionSystem->update();
	if(!player->slowed){
		player->speed = 4;
	}
    camera->follow(player->position.x, player->position.y);
}

void Rooms::draw(AffineTransform& at) {
	Game::draw(at);
}

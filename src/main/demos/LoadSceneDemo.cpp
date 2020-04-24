#include "LoadSceneDemo.h"

#include "../../engine/events/DisplayTreeChangeEvent.h"

using namespace std;

LoadSceneDemo::LoadSceneDemo() : Game(1200, 800) {
    instance = this;

    this->collisionSystem = new CollisionSystem();

    this->camera = std::make_shared<Camera>();
    this->camera->position = {this->windowWidth / 2, this->windowHeight / 2};
    this->camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
    this->container->addChild(this->camera);

    this->player = std::make_shared<Player>();
	player->position = {0, 0};
	player->width = 110;
	player->height = 80;
	player->pivot = {50, 50};
	player->play("Idle");

    this->scene = std::make_shared<Scene>(this->camera, this->player);
    this->scene->loadScene("./resources/loadSceneDemo/three_archer_very_scary.json");
    this->scene->getChild(0)->addChild(player);
    this->scene->camera = this->camera;

    this->camera->addChild(this->scene);
}

LoadSceneDemo::~LoadSceneDemo() {
    delete this->collisionSystem;
}

void LoadSceneDemo::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    //If there isn't controller input, take keyboard input. Otherwise ignore keyboard input.

    int DEAD_ZONE = 8000;
    if (pressedButtons.empty() && abs(joystickState.xVal1) - DEAD_ZONE < 0 && abs(joystickState.yVal1) - DEAD_ZONE < 0 
                               && abs(joystickState.xVal2) - DEAD_ZONE < 0 && abs(joystickState.yVal2) - DEAD_ZONE < 0){

	} else{

	}

    // Check for collisions after we finalize ideal positions
    this->collisionSystem->update();
    Game::update(pressedKeys, joystickState, pressedButtons);
}

void LoadSceneDemo::draw(AffineTransform& at) {
    Game::draw(at);
}

void LoadSceneDemo::draw_post() {

}

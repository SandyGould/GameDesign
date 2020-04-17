#include "LoadSceneDemo.h"

#include "../../engine/events/DisplayTreeChangeEvent.h"

using namespace std;

LoadSceneDemo::LoadSceneDemo() : Game(1200, 800) {
    instance = this;

    this->collisionSystem = new CollisionSystem();
    EventDispatcher::getInstance().addEventListener(this->collisionSystem, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

    this->camera = new Camera();
    this->camera->position = {this->windowWidth / 2, this->windowHeight / 2};
    this->camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
    instance->addChild(this->camera);

    this->scene = new Scene();

    this->player = new Player();
	player->position = {0, 0};
	player->width = 110;
	player->height = 80;
	player->pivot = {50, 50};
	player->play("Idle");

    this->scene->p = player;

    this->scene->loadScene("./resources/loadSceneDemo/three_archer_very_scary.json");
    this->scene->getChild(0)->addChild(player);
    this->scene->setCameraRef(camera);

    this->camera->addChild(this->scene);


}

LoadSceneDemo::~LoadSceneDemo() {
    delete camera;
    delete scene;
    delete player;
}

void LoadSceneDemo::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    //If there isn't controller input, take keyboard input. Otherwise ignore keyboard input.

    int DEAD_ZONE = 8000;
    if (pressedButtons.empty() && abs(joystickState.xVal1) - DEAD_ZONE < 0 && abs(joystickState.yVal1) - DEAD_ZONE < 0 
                               && abs(joystickState.xVal2) - DEAD_ZONE < 0 && abs(joystickState.yVal2) - DEAD_ZONE < 0){
        if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
            this->player->position.y -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
            this->player->position.x -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
            this->player->position.y += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
            this->player->position.x += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
            
            
        }

        if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
            
        }

        if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {

        }

        if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {

        }

	} else{

		// if (pressedButtons.find(SDL_CONTROLLER_BUTTON_A) != pressedButtons.end()){
		// 	player->scaleX += 0.1;
		// 	player->scaleY += 0.1;
		// }
		// if (pressedButtons.find(SDL_CONTROLLER_BUTTON_B) != pressedButtons.end()){
		// 	player->scaleX -= 0.1;
		// 	player->scaleY -= 0.1;
		// }
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

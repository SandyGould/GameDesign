#include "CollisionDemo.h"

using namespace std;

CollisionDemo::CollisionDemo() : Game(1200, 800) {
    instance = this;

    this->collisionSystem = new CollisionSystem();

    this->camera = std::make_shared<Camera>();
    this->camera->position = {this->windowWidth / 2, this->windowHeight / 2};
    this->camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
    this->container->addChild(this->camera);

    // Yup we're creating an invisible player for Scene
    this->player = std::make_shared<Player>();
    //this->player->visible = false;
    this->player->hitbox = {{25, 10}, {75, 10}, {25, 100}, {75, 100}};

    this->scene = std::make_shared<Scene>(this->camera, this->player);
    this->scene->loadScene("./resources/cameraDemo/loadScene.json");

    this->camera->addChild(this->scene);

    this->parentObj = std::make_shared<DisplayObject>("parent", "./resources/assets/Display_Objects/Moon.png");
    this->parentObj->type = "parent";
    this->parentObj->position = {this->windowWidth / 2 - 100, this->windowHeight / 2 - 100};
    //this->parentObj->width = this->parentObj->height = 200;
    this->parentObj->pivot = {50, 50};
    this->parentObj->scaleX = this->parentObj->scaleY = 2.0;
    this->scene->getChild(0)->addChild(this->parentObj);

    this->child1 = std::make_shared<Coin>();
    this->child1->position = {200, 0};
    this->child1->width = this->child1->height = 100;
    this->child1->pivot = {50, 50};
    this->parentObj->addChild(this->child1);

    this->child2 = std::make_shared<Coin>();
    this->child2->position = {200, 200};
    this->child2->width = this->child2->height = 30;
    this->child2->pivot = {15, 15};
    this->child2->hitboxType = HitboxType::Circle;
    this->parentObj->addChild(this->child2);

    this->parentObj->addChild(this->player);

    this->collisionSystem->watchForCollisions("coin", "coin");
}

CollisionDemo::~CollisionDemo() {
    // delete camera;
    // delete scene;
    // delete parentObj;
    // delete child1;
    // delete child2;
}

void CollisionDemo::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    //If there isn't controller input, take keyboard input. Otherwise ignore keyboard input.

    int DEAD_ZONE = 8000;
    if (pressedButtons.empty() && abs(joystickState.xVal1) - DEAD_ZONE < 0 && abs(joystickState.yVal1) - DEAD_ZONE < 0 
                               && abs(joystickState.xVal2) - DEAD_ZONE < 0 && abs(joystickState.yVal2) - DEAD_ZONE < 0){
        if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
            this->parentObj->position.y -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
            this->parentObj->position.x -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
            this->parentObj->position.y += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
            this->parentObj->position.x += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_E) != pressedKeys.end()) {
            this->parentObj->rotation -= 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
            this->parentObj->rotation += 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_F) != pressedKeys.end()) {
            this->parentObj->scaleX -= 0.1;
            this->parentObj->scaleY -= 0.1;
        }

        if (pressedKeys.find(SDL_SCANCODE_G) != pressedKeys.end()) {
            this->parentObj->scaleX += 0.1;
            this->parentObj->scaleY += 0.1;
        }

        if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
            this->child1->position.y -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
            this->child1->position.x -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
            this->child1->position.y += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
            this->child1->position.x += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
            this->child1->rotation -= 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
            this->child1->rotation += 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_N) != pressedKeys.end()) {
            if (this->child1->scaleX > 0.1 && this->child1->scaleY > 0.1){
                this->child1->scaleX -= 0.1;
                this->child1->scaleY -= 0.1;
            }
        }

        if (pressedKeys.find(SDL_SCANCODE_M) != pressedKeys.end()) {
            this->child1->scaleX += 0.1;
            this->child1->scaleY += 0.1;
        }

        if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
            this->child2->position.y -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
            this->child2->position.x -= 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
            this->child2->position.y += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
            this->child2->position.x += 5;
        }

        if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
            this->child2->rotation -= 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end()) {
            this->child2->rotation += 0.0314159265;
        }

        if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
            if (this->child2->scaleX > 0.1 && this->child2->scaleY > 0.1){
                this->child2->scaleX -= 0.1;
                this->child2->scaleY -= 0.1;
            }
        }

        if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
            this->child2->scaleX += 0.1;
            this->child2->scaleY += 0.1;
        }

	} else{
		this->child1->position.x += joystickState.xVal1/8000;
		this->child1->position.y += joystickState.yVal1/8000;
        this->child2->position.x += joystickState.xVal2/8000;
		this->child2->position.y += joystickState.yVal2/8000;
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

void CollisionDemo::draw(AffineTransform& at) {
    Game::draw(at);
}

void CollisionDemo::draw_post() {
    this->parentObj->drawHitbox();
    this->child1->drawHitbox();
    this->child2->drawHitcircle();
    this->player->drawHitbox();
}

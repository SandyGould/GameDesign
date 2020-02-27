#include "MyGame.h"

#include <iostream>

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	instance = this;
	curScene = new Scene();
	instance->addChild(curScene);
}

MyGame::MyGame(string sceneToLoad) : Game(1200, 1000){
	instance = this;
	curScene = new Scene();

	//To be uncommented when we have actual scenes to load
	//This way is just easier to test for now

	
	
	camera = new Camera();
	printf("new camera\n");
	camera->position = {600, 500};
	camera->pivot = {600, 500};
	printf("Camera position set\n");
	instance->addChild(camera);
	
	printf("instance added child\n");
	camera->setTopLimit(-50);
	camera->setLeftLimit(0);
	camera->setRightLimit(800);
	camera->setBottomLimit(830);

	curScene->loadScene(sceneToLoad);
	printf("Loaded scene\n");
	camera->addChild(curScene);
	printf("Camera added scene\n");
	cout << sceneToLoad << endl;

	//camera->addChild(scene);
	//printf("Camera added child\n");
	crosshair = new Crosshair();
	printf("Crosshair created\n");
	crosshair->position = {0, 0};
	crosshair->width = crosshair->height = 100;
	crosshair->pivot = {50, 50};
	


	curScene->addChild(crosshair);
	printf("Scene added crosshair\n");

	//crosshair_proto = new crosshair();

	//for(int z = 0; z < j["Sprite"].size(); z++){
        // std::cout << j["Sprite"][z] << endl;
      //  Sprite* temp_sprite = new Sprite(j["Sprite"][z]["name"], j["Sprite"][z]["filepath"]);
        //this->addChild(temp_sprite);
    //}
}

MyGame::~MyGame() {
}

void MyGame::update(std::set<SDL_Scancode> pressedKeys) {
	if (crosshair->position.y > -50 && crosshair->position.y < 50){
		if(!inZone){
			inZone = true;
			// std::cout << "zoom in" << std::endl;
			camera->zoomIn(2);
		}
	}
	else{
		if(inZone){
			// std::cout << "zoom out" << std::endl;
			inZone = false;
			camera->zoomOut(2);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		if (crosshair->position.x < 120 || (crosshair->position.y >= 680 && crosshair->position.x <= 1160)) {
			crosshair->position.x += 5;
			// camera->follow(-1 * camera->scaleX * crosshair->position.x + 600, -1 * camera->scaleY * crosshair->position.y + 500);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		if (crosshair->position.x > -140) {
			crosshair->position.x -= 5;
			// camera->follow(-1 * camera->scaleX * crosshair->position.x + 600, -1 * camera->scaleY *crosshair->position.y + 500);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		if (crosshair->position.y < 925) {
			crosshair->position.y += 5;
			// camera->follow(-1 *camera->scaleX* crosshair->position.x + 600, -1 *camera->scaleY *  crosshair->position.y + 500);
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (crosshair->position.y > -750) {
			if ((crosshair->position.x> 120 && crosshair->position.y> 680) || crosshair->position.x <= 120) {
				crosshair->position.y -= 5;
				// camera->follow(-1 * camera->scaleX * crosshair->position.x + 600, -1 * camera->scaleY * crosshair->position.y + 500);
			}
		}
	}
	camera->follow(crosshair->position.x, crosshair->position.y);
	// camera->pivot.y = crosshair->position.y;
	// to test zoom (delete for demo)
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end()) {
		if(hasChild == false)
		{
			Coin * childcoin = new Coin();
			crosshair->addChild(childcoin);
			hasChild = true;		
		}
		else
		{
			DisplayObject * mycoin = crosshair->getChild(0);
			crosshair->removeImmediateChild(mycoin);
			hasChild = false;
		}
	}
	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
		if(hasChild == true)
		{
			DisplayObject* mycoin = crosshair->getChild(0);
			Coin * newcoin = new Coin();
			bool visible = true;
			newcoin->position = mycoin->position;
			newcoin->width = mycoin->width;
			newcoin-> height = mycoin->height;
			newcoin->pivot = mycoin->pivot;
			newcoin->scaleX = mycoin->scaleX;
			newcoin->scaleY = mycoin->scaleY;
			newcoin->rotation = mycoin->rotation; // in radians
			

			bool hasCollision = false;
			crosshair->removeImmediateChild(mycoin);
			printf("About to add child to scene\n");
			curScene->addChild(newcoin);
			printf("Child added?\n");
			hasChild = false;	
		}
		
	}
	

	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (crosshair->position.y > -750) {
			if ((crosshair->position.x> 120 && crosshair->position.y> 680) || crosshair->position.x <= 120) {
				crosshair->position.y -= 5;
				camera->follow(-1 * camera->scaleX * crosshair->position.x + 600, -1 * camera->scaleY * crosshair->position.y + 500);
			}
		}
	}

	// to test zoom (delete for demo)
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	
	//if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
	//	if(allSprites->getChild("scene1") != NULL){
	//		allSprites->addChild(scene2);
	//		allSprites->children.erase(std::remove(allSprites->children.begin(), allSprites->children.end(), scene), allSprites->children.end());
	//	}
	//	else if(allSprites->getChild("scene2") != NULL){
	//		allSprites->addChild(scene);
	//		allSprites->children.erase(std::remove(allSprites->children.begin(), allSprites->children.end(), scene2), allSprites->children.end());
	//	}
	//}

	
	
	
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
}
#include "MyGame.h"

#include "../engine/events/ClickEvent.h"
#include "../engine/events/DragEvent.h"

#include <iostream>

using namespace std;

MyGame::MyGame() : MyGame("./resources/scene/blank.json"){
	
}


void MyGame::setupfiles(string path)
{
	if(path.compare("./resources/other/") == 0 || path.compare("./resources/scene/") == 0)
	{
		return;
	}
	DIR *dir;
	struct dirent *ent;

	if((dir = opendir(path.c_str()) )!= NULL)
	{
		while((ent = readdir(dir) )!= NULL)
		{

			if(!ent->d_name || ent->d_name[0] == '.')
			{
				continue;
			}
			else if(ent->d_type == DT_DIR)
			{
				setupfiles(path+ent->d_name+"/");
			}
			else
			{
				printf("%s\n",ent->d_name);
				all_sprites.push_back(path+ent->d_name);
			}

		}
		closedir(dir);
	}
	else
	{
		perror("");
		printf("Could not open...");
	}
}

MyGame::MyGame(string sceneToLoad) : Game(1200, 1000){
	instance = this;
	curScene = new Scene();
	
	camera = new Camera();
	printf("new camera\n");
	camera->position = {600, 500};
	camera->pivot = {600, 500};
	printf("Camera position set\n");
	instance->addChild(camera);

	printf("instance added child\n");
	//camera->setTopLimit(-50);
	//camera->setLeftLimit(0);
	//camera->setRightLimit(800);
	//camera->setBottomLimit(830);

	curScene->loadScene(sceneToLoad);
	printf("Loaded scene\n");

	for (const auto& object : curScene->children) {
		this->addEventListener(object, ClickEvent::CLICK_EVENT);
		this->addEventListener(object, DragEvent::DRAG_EVENT);
	}
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



	camera->addChild(crosshair);
	printf("Scene added crosshair\n");



	Coin *coin_proto = new Coin();
	all_objects.addChild(coin_proto);
	Player *player_proto = new Player();
	all_objects.addChild(player_proto);
	setupfiles("./resources/");
	printf("Allsprites size = %d\n", all_sprites.size());


	//crosshair_proto = new crosshair();

	//for(int z = 0; z < j["Sprite"].size(); z++){
        // std::cout << j["Sprite"][z] << endl;
      //  Sprite* temp_sprite = new Sprite(j["Sprite"][z]["name"], j["Sprite"][z]["filepath"]);
        //this->addChild(temp_sprite);
    //}
}

//change this to containers
void MyGame::copyDisplayObjectContainer(DisplayObjectContainer *newobj, DisplayObjectContainer *oldobj) {
	newobj->position = oldobj->position;
	newobj->width = oldobj->width;
	newobj-> height = oldobj->height;
	newobj->pivot = oldobj->pivot;
	newobj->scaleX = oldobj->scaleX;
	newobj->scaleY = oldobj->scaleY;
	newobj->rotation = oldobj->rotation; // in radians
	newobj->facingRight = oldobj->facingRight;
	newobj->hasCollision = oldobj->hasCollision;
	copy(oldobj->children.begin(),oldobj->children.end(),back_inserter(newobj->children));
	copy(oldobj->collisionList.begin(),oldobj->collisionList.end(),back_inserter(newobj->collisionList));
	newobj->id = oldobj->id;
	newobj->imgPath = oldobj->imgPath;
	newobj->loadTexture(newobj->imgPath);


}


void MyGame::copyDisplayObject(DisplayObject *newobj, DisplayObject *oldobj) {
	newobj->position = oldobj->position;
	newobj->width = oldobj->width;
	newobj-> height = oldobj->height;
	newobj->pivot = oldobj->pivot;
	newobj->scaleX = oldobj->scaleX;
	newobj->scaleY = oldobj->scaleY;
	newobj->rotation = oldobj->rotation; // in radians
	newobj->facingRight = oldobj->facingRight;
	newobj->hasCollision = oldobj->hasCollision;
	copy(static_cast<DisplayObjectContainer*>(oldobj)->children.begin(),(static_cast<DisplayObjectContainer*>(oldobj)->children.end()),back_inserter((static_cast<DisplayObjectContainer*>(newobj)->children)));
	copy(static_cast<DisplayObjectContainer*>(oldobj)->collisionList.begin(),static_cast<DisplayObjectContainer*>(oldobj)->collisionList.end(),back_inserter(static_cast<DisplayObjectContainer*>(newobj)->collisionList));
	newobj->id = oldobj->id;
	newobj->imgPath = oldobj->imgPath;
	newobj->loadTexture(newobj->imgPath);
	///Coin *coin_proto = new Coin();
	//all_objects.addChild(coin_proto);
	//Player *player_proto = new Player();
	//all_objects.addChild(player_proto);
}

MyGame::~MyGame() {
}

void MyGame::update(std::unordered_set<SDL_Scancode> pressedKeys) {
	/*
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
	*/

	//Move
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		crosshair->position.x += 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		crosshair->position.x -= 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		crosshair->position.y += 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		crosshair->position.y -= 5;
	}

	camera->follow(crosshair->position.x, crosshair->position.y);

	// camera->pivot.y = crosshair->position.y;

	// Zoom
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	if (pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end() && prevKeys.find(SDL_SCANCODE_TAB) == prevKeys.end()) {
		if(grabbedObj == false)
		{
			if(pressedKeys.find(SDL_SCANCODE_LSHIFT) != pressedKeys.end() || pressedKeys.find(SDL_SCANCODE_RSHIFT) != pressedKeys.end()){
				if(obj_ind > 1)
				{
					printf("obj_ind == %d\n",obj_ind);

					DisplayObject * myobjc = crosshair->getChild(0);
					crosshair->removeImmediateChild(myobjc);

					--obj_ind;
					Sprite * newobj = new Sprite("newobject",all_sprites[obj_ind]);
					//DisplayObject * childobj = all_objects.getChild(obj_ind);
					//DisplayObject * newobj = new DisplayObject();
					//copyDisplayObject(newobj,childobj);
					crosshair->addChild(newobj);
					hasChild = true;
				}
				else
				{
					if(obj_ind == 1){
						obj_ind = 0;
						DisplayObject * myobjc = crosshair->getChild(0);
						crosshair->removeImmediateChild(myobjc);
						hasChild = false;
					}else{
						obj_ind = all_sprites.size()-1;
						Sprite * newobj = new Sprite("newobject",all_sprites[obj_ind]);
						crosshair->addChild(newobj);
						hasChild = true;
					}
					
				}
			} else{
				if(obj_ind < all_sprites.size()-1)
				{
					printf("obj_ind == %d\n",obj_ind);
					if(obj_ind > 0)
					{
						DisplayObject * myobjc = crosshair->getChild(0);
						crosshair->removeImmediateChild(myobjc);
					}
					obj_ind++;
					Sprite * newobj = new Sprite("newobject",all_sprites[obj_ind]);
					//DisplayObject * childobj = all_objects.getChild(obj_ind);
					//DisplayObject * newobj = new DisplayObject();
					//copyDisplayObject(newobj,childobj);
					crosshair->addChild(newobj);
					hasChild = true;
				}
				else
				{
					obj_ind = 0;
					DisplayObject * myobjc = crosshair->getChild(0);
					crosshair->removeImmediateChild(myobjc);
					hasChild = false;
				}
			}
		//	Coin * childcoin = new Coin();
		//	crosshair->addChild(childcoin);
		//	hasChild = true;
		}
		//else
		//{
		//	DisplayObject * mycoin = crosshair->getChild(0);
		//	crosshair->removeImmediateChild(mycoin);
		//	hasChild = false;
		//}
	}

	if (pressedKeys.find(SDL_SCANCODE_BACKSPACE) != pressedKeys.end()){
		if(obj_ind != 0){
			obj_ind = 0;
			DisplayObject * myobjc = crosshair->getChild(0);
			crosshair->removeImmediateChild(myobjc);
			hasChild = false;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
		if(hasChild == true || grabbedObj == true)
		{
			DisplayObject* myobj = crosshair->getChild(0);
			DisplayObject* newobj = new DisplayObjectContainer();
			copyDisplayObject(newobj,myobj);
			newobj->position = crosshair->position;
			curScene->addChild(newobj);
			crosshair->removeImmediateChild(myobj);
			hasChild = false;
			obj_ind = 0;
			grabbedObj = false;

			this->addEventListener(newobj, ClickEvent::CLICK_EVENT);
			this->addEventListener(newobj, DragEvent::DRAG_EVENT);

			//bool visible = true;
			//newcoin->position = mycoin->position;
			//newcoin->width = mycoin->width;
			//newcoin-> height = mycoin->height;
			//newcoin->pivot = mycoin->pivot;
			//newcoin->scaleX = mycoin->scaleX;
			//newcoin->scaleY = mycoin->scaleY;
			//newcoin->rotation = mycoin->rotation; // in radians


			//bool hasCollision = false;
			//crosshair->removeImmediateChild(mycoin);
			//printf("About to add child to scene\n");
			//curScene->addChild(newcoin);
			//printf("Child added?\n");
			//hasChild = false;
		}

	}

	/*
	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (crosshair->position.y > -750) {
			if ((crosshair->position.x> 120 && crosshair->position.y> 680) || crosshair->position.x <= 120) {
				crosshair->position.y -= 5;
				camera->follow(-1 * camera->scaleX * crosshair->position.x + 600, -1 * camera->scaleY * crosshair->position.y + 500);
			}
		}
	}
	*/

	//Pivot
	if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
		heldPivot.y -= 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
		heldPivot.x -= 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
		heldPivot.y += 5;
	}
	if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
		heldPivot.x += 5;
	}
	if (hasChild){
		crosshair->getChild(0)->pivot = heldPivot;
	}

	//Rotation
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		heldRotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		heldRotation += 0.05;
	}
	if (hasChild){
		crosshair->getChild(0)->rotation = heldRotation;
	}

	//Scaling
	if (pressedKeys.find(SDL_SCANCODE_MINUS) != pressedKeys.end()) {
		heldScaleX -= 0.05;
		heldScaleY -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_EQUALS) != pressedKeys.end()) {
		heldScaleX += 0.05;
		heldScaleY += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
		heldScaleX -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		heldScaleX += 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_LEFTBRACKET) != pressedKeys.end()) {
		heldScaleY -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHTBRACKET) != pressedKeys.end()) {
		heldScaleY += 0.05;
	}
	if (hasChild){
		crosshair->getChild(0)->scaleX = heldScaleX;
		crosshair->getChild(0)->scaleY = heldScaleY;
	}

	// to test zoom (delete for demo)
	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end() && pressedKeys.find(SDL_SCANCODE_LCTRL) == pressedKeys.end() && pressedKeys.find(SDL_SCANCODE_RCTRL) == pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	
	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		if (crosshair != NULL){
			SDL_Point tempPoint = crosshair->getGlobalPosition(atTest);
			cout << tempPoint.x << ", " << tempPoint.y << endl;
		}
	}

	if ((pressedKeys.find(SDL_SCANCODE_LCTRL) != pressedKeys.end() || pressedKeys.find(SDL_SCANCODE_RCTRL) != pressedKeys.end()) && pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		string tmp;
		cin >> tmp;
		curScene->saveScene(tmp);
	}

	if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()){
		heldPosition = {0, 0};
		heldPivot = {0, 0};
		heldScaleX = 1.0;
		heldScaleY = 1.0;
		heldRotation = 0.0;
		if (hasChild){
			DisplayObject* tmp = crosshair->getChild(0);
			tmp->position = heldPosition;
			tmp->pivot = heldPivot;
			tmp->scaleX = heldScaleX;
			tmp->scaleY = heldScaleY;
			tmp->rotation = heldRotation;
		}
	}

	prevKeys = pressedKeys;
	
	Game::update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	SDL_RenderClear(Game::renderer);
	SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(Game::renderer, 600-crosshair->position.x, 0, 600-crosshair->position.x, 1000);
	SDL_RenderDrawLine(Game::renderer, 0, 500-crosshair->position.y, 1200, 500-crosshair->position.y);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	Game::draw(at);
}

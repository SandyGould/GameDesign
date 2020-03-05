#include "Editor.h"

#include "../engine/events/ClickEvent.h"
#include "../engine/events/DragEvent.h"

#include <iostream>

Editor::Editor() : Editor("./resources/scene/blank.json") {

}

Editor::Editor(const string& sceneToLoad) : Game(1200, 800) {
	instance = this;
	curScene = new Scene();

	camera = new Camera();
	camera->position = {this->windowWidth / 2, this->windowHeight / 2};
	camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
	instance->addChild(camera);

	curScene->loadScene(sceneToLoad);

	camera->addChild(curScene);

	crosshair = new Crosshair();
	crosshair->position = {0, 0};
	crosshair->width = crosshair->height = 100;
	crosshair->pivot = {50, 50};

	camera->addChild(crosshair);

	this->dispatcher.addEventListener(this, ClickEvent::CLICK_EVENT);
	this->dispatcher.addEventListener(this, DragEvent::DRAG_EVENT);

	setupfiles("./resources/");
}

void Editor::setupfiles(const string& path) {
	if (path.compare("./resources/other/") == 0 || path.compare("./resources/scene/") == 0) {
		return;
	}
	DIR* dir;
	struct dirent* ent;

	if ((dir = opendir(path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {

			if (!ent->d_name || ent->d_name[0] == '.') {
				continue;
			} else if (ent->d_type == DT_DIR) {
				setupfiles(path + ent->d_name + "/");
			} else {
				all_sprites.push_back(path + ent->d_name);
			}

		}
		closedir(dir);
	} else {
		perror("");
		printf("Could not open...");
	}
}

void Editor::update(std::unordered_set<SDL_Scancode> pressedKeys) {
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

	// Zoom
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		camera->zoomIn(1.1);
	}
	if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) {
		camera->zoomOut(1.1);
	}

	if (pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end() && prevKeys.find(SDL_SCANCODE_TAB) == prevKeys.end()) {
		if (grabbedObj == false) {
			if (pressedKeys.find(SDL_SCANCODE_LSHIFT) != pressedKeys.end() || pressedKeys.find(SDL_SCANCODE_RSHIFT) != pressedKeys.end()) {
				if (obj_ind > 1) {
					printf("obj_ind == %d\n", obj_ind);

					DisplayObject* myobjc = crosshair->getChild(0);
					crosshair->removeImmediateChild(myobjc);

					--obj_ind;
					Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
					//DisplayObject * childobj = all_objects.getChild(obj_ind);
					//DisplayObject * newobj = new DisplayObject();
					//copyDisplayObject(newobj,childobj);
					crosshair->addChild(newobj);
					hasChild = true;
				} else {
					if (obj_ind == 1) {
						obj_ind = 0;
						DisplayObject* myobjc = crosshair->getChild(0);
						crosshair->removeImmediateChild(myobjc);
						hasChild = false;
					} else {
						obj_ind = all_sprites.size() - 1;
						Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
						crosshair->addChild(newobj);
						hasChild = true;
					}

				}
			} else {
				if (obj_ind < all_sprites.size() - 1) {
					if (obj_ind > 0) {
						DisplayObject* myobjc = crosshair->getChild(0);
						crosshair->removeImmediateChild(myobjc);
					}
					obj_ind++;
					Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
					crosshair->addChild(newobj);
					hasChild = true;
				} else {
					obj_ind = 0;
					DisplayObject* myobjc = crosshair->getChild(0);
					crosshair->removeImmediateChild(myobjc);
					hasChild = false;
				}
			}
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_BACKSPACE) != pressedKeys.end()) {
		if (obj_ind != 0) {
			obj_ind = 0;
			DisplayObject* myobjc = crosshair->getChild(0);
			crosshair->removeImmediateChild(myobjc);
			hasChild = false;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
		if (hasChild == true || grabbedObj == true) {
			DisplayObject* myobj = crosshair->getChild(0);
			DisplayObject* newobj = new DisplayObject(*myobj);
			newobj->position = crosshair->position;
			curScene->addChild(newobj);
			crosshair->removeImmediateChild(myobj);
			hasChild = false;
			obj_ind = 0;
			grabbedObj = false;
		}
	}

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
	if (hasChild) {
		crosshair->getChild(0)->pivot = heldPivot;
	}

	//Rotation
	if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
		heldRotation -= 0.05;
	}
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		heldRotation += 0.05;
	}
	if (hasChild) {
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
	if (hasChild) {
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
		if (crosshair != NULL) {
			SDL_Point tempPoint = crosshair->getGlobalPosition(atTest);
			cout << tempPoint.x << ", " << tempPoint.y << endl;
		}
	}

	if ((pressedKeys.find(SDL_SCANCODE_LCTRL) != pressedKeys.end() || pressedKeys.find(SDL_SCANCODE_RCTRL) != pressedKeys.end()) && pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		string tmp;
		cin >> tmp;
		curScene->saveScene(tmp);
	}

	if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
		heldPosition = {0, 0};
		heldPivot = {0, 0};
		heldScaleX = 1.0;
		heldScaleY = 1.0;
		heldRotation = 0.0;
		if (hasChild) {
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

void Editor::draw(AffineTransform& at) {
	SDL_RenderClear(Game::renderer);
	SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(Game::renderer, this->windowWidth / 2 - crosshair->position.x, 0, this->windowWidth / 2 - crosshair->position.x, this->windowHeight);
	SDL_RenderDrawLine(Game::renderer, 0, this->windowHeight / 2 - crosshair->position.y, this->windowWidth, this->windowHeight / 2 - crosshair->position.y);
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	Game::draw(at);
}

void Editor::handleEvent(Event* e) {
	if (e->getType() == ClickEvent::CLICK_EVENT) {
		ClickEvent* event = static_cast<ClickEvent*>(e);
		this->selectObject(this, event->x, event->y);
		

	} else if (e->getType() == DragEvent::DRAG_EVENT) {
		DragEvent* event = static_cast<DragEvent*>(e);
		this->dragObject(this, event->x, event->y, event->xrel, event->yrel);
	}
}

bool Editor::selectObject(DisplayObject* object, int x, int y) {
	if (object->type != "DisplayObject") {
		DisplayObjectContainer* container = static_cast<DisplayObjectContainer*>(object);
		for (auto it = container->children.crbegin(); it != container->children.crend(); it++) {
			if (this->selectObject(*it, x, y)) {
				return true;
			}
		}
	}

	if (object->dstrect.x <= x && x <= object->dstrect.x + object->dstrect.w &&
		object->dstrect.y <= y && y <= object->dstrect.y + object->dstrect.h) {
		std::cout << object->id << " handling a mouse event at (" << x << ", " << y << ")" << std::endl;
		return true;
	}
	return false;
}

bool Editor::dragObject(DisplayObject* object, int x, int y, int xrel, int yrel) {
	if (object->type != "DisplayObject") {
		DisplayObjectContainer* container = static_cast<DisplayObjectContainer*>(object);
		for (auto it = container->children.crbegin(); it != container->children.crend(); it++) {
			if (this->dragObject(*it, x, y, xrel, yrel)) {
				return true;
			}
		}
	}

	// Move the object to follow the mouse
	if (object->dstrect.x <= x && x <= object->dstrect.x + object->dstrect.w &&
		object->dstrect.y <= y && y <= object->dstrect.y + object->dstrect.h) {
		object->position.x += xrel;
		object->position.y += yrel;
		return true;
	}
	return false;
}

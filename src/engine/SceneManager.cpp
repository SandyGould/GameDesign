#include "SceneManager.h"
#include "events/NewSceneEvent.h"
#include "events/TweenEvent.h"
#include "Camera.h"
#include "things/Player.h"
#include "tweens/TweenJuggler.h"

#include <string.h>
#include <iostream>


SceneManager::SceneManager(shared_ptr<Camera> c, shared_ptr<Player> p) {
    this->p = p;
    this->c = c;
    // scene pointers - head and tail are dummy scene nodes
    this->head = std::make_shared<Scene>("empty_scene_head");
    this->tail = std::make_shared<Scene>("empty_scene_tail");
    this->currScene = NULL;
    this->iter = NULL;
    // set up linked list
    this->head->nextScene = this->tail;
    this->tail->prevScene = this->head;
}


SceneManager::~SceneManager() {
    this->clearArea();
    // delete this->iter;
    // delete this->head;
    // delete this->tail;
}


void SceneManager::loadArea(int area, int rooms) { // each area must have at least 2 rooms
    std::string areaNo = std::to_string(area);
    // set head and tail
    for (int i = 1; i <= rooms; i++) {
        std::string roomNo = std::to_string(i);
        auto scene = std::make_shared<Scene>("scene" + roomNo);
        scene->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
        std::cout << scene->scenePath << std::endl;
        // add current scene to SceneManager's scenes
        this->addScene(scene);
    }
    this->currRoom = 1;
}


void SceneManager::loadAllAreas(int areas) {
    // load all the areas into the linked list at once
    for (int a = 1; a <= areas; a++) {
        loadArea(a, this->numRooms[a-1]);
    }
}


void SceneManager::loadNewArea(int area, int rooms) { // not functioning correctly atm
    std::string areaNo = std::to_string(area);
    this->iter = this->head;
    // set head and tail
    for (int i = 1; i <= rooms; i++) {
        std::string roomNo = std::to_string(i);
        this->iter = this->iter->nextScene;
        if (this->iter == this->tail) {
            auto scene = std::make_shared<Scene>("scene" + roomNo);
            scene->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
            // add current scene to SceneManager's scenes
            this->addScene(scene);
        }
        else {
            this->iter->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
        }   
    }
    this->currRoom = 1;
}

void SceneManager::clearArea() {
    this->iter = this->head->nextScene;
    while (this->iter->nextScene != NULL) {
        this->deleteScene(this->iter->id);
        this->iter = this->iter->nextScene;
    }
    this->roomsCount = 0;
}


std::shared_ptr<Scene> SceneManager::findScene(std::string id) {
    this->iter = this->head;
    while (this->iter != this->tail) {
        if (this->iter->id == id) {
            return this->iter;
        }
        else {
            this->iter = this->iter->nextScene;
        }
    }
    return nullptr;
}


void SceneManager::addScene(shared_ptr<Scene> scene) { // insert at tail
    shared_ptr<Scene> newScene = scene;
    newScene->prevScene = this->tail->prevScene;
    newScene->nextScene = this->tail;
    this->tail->prevScene->nextScene = newScene;
    this->tail->prevScene = newScene;
    this->roomsCount++;    
}


void SceneManager::deleteScene(std::string id) {
    this->iter = this->head;
    while (this->iter != this->tail) {
        if (this->iter->id == id) {
            this->iter->prevScene->nextScene = this->iter->nextScene;
            this->iter->nextScene->prevScene = this->iter->prevScene;;
            this->roomsCount--;
            // delete any remaining events
            if (EventDispatcher::getInstance().hasEventListener(iter.get(), NewSceneEvent::FADE_OUT_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter.get(), NewSceneEvent::FADE_OUT_EVENT);
	        }
            if (EventDispatcher::getInstance().hasEventListener(iter.get(), NewSceneEvent::FADE_IN_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter.get(), NewSceneEvent::FADE_IN_EVENT);
	        }
            if (EventDispatcher::getInstance().hasEventListener(iter.get(), NewSceneEvent::SCALE_OUT_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter.get(), NewSceneEvent::SCALE_OUT_EVENT);
	        }
            // delete iter;
            break;
        }
        else {
            this->iter = this->iter->nextScene;
        }
    }
}


void SceneManager::loadFirstScene() {
    // set current number of rooms based on area
    this->roomsCount = this->numRooms[this->currArea-1];

    this->currScene = this->head->nextScene;
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;
    
    // EVENTS FOR UNLOADING
    // create fade out event listener for this scene
    EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_OUT_EVENT);

    // EVENTS FOR LOADING
    // create fade in event listener for this scene
    EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_IN_EVENT);
    
    this->currScene->loadScene(this->currScene->scenePath);
	
    // load player info
    p->position = this->currScene->playerEntrancePos;
    p->width = p->height = 50;
    this->currScene->addChild(p);

    // set camera limits - still need to do
    c->position = this->currScene->camEntrancePosition;
    c->pivot = this->currScene->camEntrancePivot;
    c->addChild(this->currScene);

    // create collision system
    this->collisionSystem = std::make_shared<CollisionSystem>();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "enemy");

    std::cout << this->c->position.y << std::endl;
    // add tween complete event for scene manager
	if (!EventDispatcher::getInstance().hasEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT)) {
	    EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
    }
}

void SceneManager::unloadScene() {
    // queue fade out transition (or scale out, if this is the last scene in the area)
    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_OUT_EVENT));
    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::SCALE_OUT_EVENT));
}


void SceneManager::loadNextScene() {
    if (this->currScene->nextScene == this->tail) {
        this->currScene = std::make_shared<Scene>();
        new_area_text = std::make_shared<TextBox>("start_text", "Game Over");
	    new_area_text->position = {300, 200};
	    this->currScene->addChild(new_area_text);
        return;
    }
    this->currScene = currScene->nextScene;
    this->currRoom++;

    if (this->currRoom > this->roomsCount) {
        this->currArea++;
        this->currRoom = 1;
        this->roomsCount = numRooms[this->currArea - 1];
    }
    
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;
    
    // create fade out event listener for this scene
    if (!EventDispatcher::getInstance().hasEventListener(this, NewSceneEvent::FADE_OUT_EVENT)) {
        EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_OUT_EVENT);
    }
    if (!EventDispatcher::getInstance().hasEventListener(this, NewSceneEvent::FADE_IN_EVENT)) {
        EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_IN_EVENT);
    }
    
    // load the scene
    this->currScene->loadScene(this->currScene->scenePath);

    // load player
    p->position = this->currScene->playerEntrancePos;
    p->width = p->height = 50;
    this->currScene->addChild(p);

    // set camera limits - still need to do
    c->position = this->currScene->camEntrancePosition;
    c->pivot = this->currScene->camEntrancePivot;
    c->addChild(this->currScene);

    // create collision system
    // delete collisionSystem;
    this->collisionSystem = std::make_shared<CollisionSystem>();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "enemy");

    if (this->currRoom == 1) {
        new_area_text = std::make_shared<TextBox>("start_text", "Area " + std::to_string(this->currArea));
	    new_area_text->position = {300, 200};
	    this->currScene->addChild(new_area_text);
    }
}


void SceneManager::loadPrevScene() {
    // change SceneManager's current scene
    this->currScene = currScene->prevScene;
    this->currRoom--;
    // load player
    this->currScene->addChild(this->p);
    this->currScene->player = p;
    // add to camera
    this->c->addChild(this->currScene);
    this->currScene->camera = c;
    
    // EVENTS FOR UNLOADING
    // create fade out event listener for this scene
    EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_OUT_EVENT);
    
    // EVENTS FOR LOADING
    // create fade in event
    EventDispatcher::getInstance().addEventListener(currScene.get(), NewSceneEvent::FADE_IN_EVENT);

    // load player
    p->position = this->currScene->playerExitPos;
    p->width = p->height = 50;

    // set camera limits - still need to do
    c->position = this->currScene->camExitPosition;
    c->pivot = this->currScene->camExitPivot;
}


void SceneManager::updateScene() {
    // if forward condition is satisfied, transition to next scene
    if (this->currScene->forward_coord == "x" && this->currScene->forward_comp == ">") {
        if (p->position.x > this->currScene->goForward.x) {
            this->sceneChange = "next";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "x" && this->currScene->forward_comp == "<") {
        if (p->position.x < this->currScene->goForward.x) {
            this->sceneChange = "next";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "y" && this->currScene->forward_comp == ">") {
        if (p->position.y > this->currScene->goForward.y) {
            this->sceneChange = "next";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "y" && this->currScene->forward_comp == "<") {
        if (p->position.y < this->currScene->goForward.y) {
            this->sceneChange = "next";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }

    // if backward condition is satisfied, go back to previous scene
    if (this->currScene->back_coord == "x" && this->currScene->back_comp == ">") {
        if (p->position.x > this->currScene->goBack.x) {
            this->sceneChange = "previous";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->back_coord == "x" && this->currScene->back_comp == "<") {
        if (p->position.x < this->currScene->goBack.x) {
            this->sceneChange = "previous";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->back_coord == "y" && this->currScene->back_comp == ">") {
        if (p->position.y < this->currScene->goBack.y) {
            this->sceneChange = "previous";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->back_coord == "y" && this->currScene->back_comp == "<") {
        if (p->position.y < this->currScene->goBack.y) {
            this->sceneChange = "previous";
            this->currScene->removeImmediateChildWithoutDelete(p);
            this->unloadScene();
            return;
        }
    }
    this->collisionSystem->update();
}


void SceneManager::handleEvent(Event* e) {
    if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT) {
        EventDispatcher::getInstance().removeEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
        // fade out transition
        if (((TweenEvent*) e)->getTween()->getID() == currScene->id + "_out_transition") {
            this->c->removeImmediateChildWithoutDelete(currScene);
            if (this->sceneChange == "previous") {
                this->loadPrevScene();
            }
            else {
                this->loadNextScene();
            }
            // queue scene transition
            EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_IN_EVENT));
            // add tween complete event for scene manager
            if (!EventDispatcher::getInstance().hasEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT)) {
	            EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
            }
        }
    }
}
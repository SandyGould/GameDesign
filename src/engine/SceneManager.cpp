#include "SceneManager.h"
#include "events/NewSceneEvent.h"
#include "events/TweenEvent.h"
#include "Camera.h"
#include "things/Player.h"

#include <string.h>
#include <iostream>

SceneManager::SceneManager(Camera* c, Player* p) {
    this->p = p;
    this->c = c;
    // scene pointers - head and tail are dummy scene nodes
    this->head = new Scene("empty_scene_head");
    this->tail = new Scene("empty_scene_tail");
    this->currScene = NULL;
    this->iter = NULL;
    // set up linked list
    this->head->nextScene = this->tail;
    this->tail->prevScene = this->head;
}

SceneManager::~SceneManager() {
    this->iter = this->head->nextScene;
    while (this->iter != this->tail) {
        this->iter = this->iter->nextScene;
        // delete any remaining events
        if (EventDispatcher::getInstance().hasEventListener(this->iter->prevScene, NewSceneEvent::FADE_OUT_EVENT)) {
		    EventDispatcher::getInstance().removeEventListener(this->iter->prevScene, NewSceneEvent::FADE_OUT_EVENT);
	    }
        if (EventDispatcher::getInstance().hasEventListener(this->iter->prevScene, TweenEvent::TWEEN_COMPLETE_EVENT)) {
		    EventDispatcher::getInstance().removeEventListener(this->iter->prevScene, TweenEvent::TWEEN_COMPLETE_EVENT);
	    }
        if (EventDispatcher::getInstance().hasEventListener(this->iter->prevScene, NewSceneEvent::FADE_IN_EVENT)) {
		    EventDispatcher::getInstance().removeEventListener(this->iter->prevScene, NewSceneEvent::FADE_IN_EVENT);
	    }    
        delete this->iter->prevScene;
    }
    delete this->head;
    delete this->tail;
}

void SceneManager::loadArea(int area, int rooms) { // each area MUST have at least 2 rooms
    std::string areaNo = std::to_string(area);
    // set head and tail
    for (int i = 1; i <= rooms; i++) {
        std::string roomNo = std::to_string(i);
        Scene* scene = new Scene("scene" + roomNo);
        scene->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
        // add current scene to SceneManager's scenes
        this->addScene(scene);
    }
}

Scene* SceneManager::findScene(std::string id) {
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

void SceneManager::addScene(Scene* scene) { // insert at tail
    Scene* newScene = scene;
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
            if (EventDispatcher::getInstance().hasEventListener(iter, NewSceneEvent::FADE_OUT_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter, NewSceneEvent::FADE_OUT_EVENT);
	        }
            if (EventDispatcher::getInstance().hasEventListener(iter, TweenEvent::TWEEN_COMPLETE_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter, TweenEvent::TWEEN_COMPLETE_EVENT);
	        }
            if (EventDispatcher::getInstance().hasEventListener(iter, NewSceneEvent::FADE_IN_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter, NewSceneEvent::FADE_IN_EVENT);
	        }
            delete iter;
            break;
        }
        else {
            this->iter = this->iter->nextScene;
        }
    }
}

void SceneManager::loadFirstScene() {
    this->currScene = this->head->nextScene;
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;
    
    // EVENTS FOR UNLOADING
    // create fade out event listener for this scene
    EventDispatcher::getInstance().addEventListener(this->currScene, NewSceneEvent::FADE_OUT_EVENT);
	// create tween complete event listener for this scene
    EventDispatcher::getInstance().addEventListener(this->currScene, TweenEvent::TWEEN_COMPLETE_EVENT);
    // create fade in event listener for this scene
    EventDispatcher::getInstance().addEventListener(currScene, NewSceneEvent::FADE_IN_EVENT);

    // load the scene
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
    this->collisionSystem = new CollisionSystem();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "enemy");

    // add tween complete event for scene manager
	EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
}

void SceneManager::unloadScene() {
    // queue fade out transition
    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_OUT_EVENT));
}

void SceneManager::loadNextScene() {
    // change SceneManager's current scene
    this->currScene = currScene->nextScene;
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;
    
    // EVENTS FOR UNLOADING
    // create fade out event listener for this scene
    if (!EventDispatcher::getInstance().hasEventListener(currScene, NewSceneEvent::FADE_OUT_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, NewSceneEvent::FADE_OUT_EVENT);
	}
    // create tween complete event listener for this scene
    if (!EventDispatcher::getInstance().hasEventListener(currScene, TweenEvent::TWEEN_COMPLETE_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, TweenEvent::TWEEN_COMPLETE_EVENT);
	}

    // EVENTS FOR LOADING
    // create fade in event
    if (!EventDispatcher::getInstance().hasEventListener(currScene, NewSceneEvent::FADE_IN_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, NewSceneEvent::FADE_IN_EVENT);
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
    delete collisionSystem;
    this->collisionSystem = new CollisionSystem();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "enemy");

    // queue scene transition
    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_IN_EVENT));
    
    // add tween complete event for scene manager
	EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
}

void SceneManager::loadPrevScene() {
    // change SceneManager's current scene
    this->currScene = currScene->prevScene;
    // load player
    this->currScene->addChild(this->p);
    this->currScene->player = p;
    // add to camera
    this->c->addChild(this->currScene);
    this->currScene->camera = c;
    
    // EVENTS FOR UNLOADING
    // create fade out event listener for this scene
    if (!EventDispatcher::getInstance().hasEventListener(currScene, NewSceneEvent::FADE_OUT_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, NewSceneEvent::FADE_OUT_EVENT);
	}
    // create tween complete event listener for this scene
    if (!EventDispatcher::getInstance().hasEventListener(currScene, TweenEvent::TWEEN_COMPLETE_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, TweenEvent::TWEEN_COMPLETE_EVENT);
	}

    // EVENTS FOR LOADING
    // create fade in event
    if (!EventDispatcher::getInstance().hasEventListener(currScene, NewSceneEvent::FADE_IN_EVENT)) {
		EventDispatcher::getInstance().addEventListener(currScene, NewSceneEvent::FADE_IN_EVENT);
	}

    // load player
    p->position = this->currScene->playerExitPos;
    p->width = p->height = 50;

    // set camera limits - still need to do
    c->position = this->currScene->camExitPosition;
    c->pivot = this->currScene->camExitPivot;

    // queue scene transition
    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_IN_EVENT));
    
    // add tween complete event for scene manager
	EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
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
        if (((TweenEvent*) e)->getTween()->getID() == currScene->id + "_out_transition") {
            this->c->removeImmediateChildWithoutDelete(currScene);
            if (this->sceneChange == "previous") {
                this->loadPrevScene();     
            }
            else {
                this->loadNextScene();
            }
        }
    }
}
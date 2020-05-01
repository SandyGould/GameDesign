#include "SceneManager.h"
#include "events/NewSceneEvent.h"
#include "events/RestartEvent.h"
#include <iostream>


SceneManager::SceneManager(shared_ptr<Camera> c, shared_ptr<Player> p) {
    this->p = p;
    this->c = c;
    // scene pointers - head and tail are dummy scene nodes
    this->head = std::make_shared<Scene>("empty_scene_head");
    this->tail = std::make_shared<Scene>("empty_scene_tail");
    this->currScene = nullptr;
    this->iter = nullptr;
    // set up linked list
    this->head->nextScene = this->tail;
    this->tail->prevScene = this->head;

    // add tween complete event for scene manager
    EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
     EventDispatcher::getInstance().addEventListener(this, RestartEvent::RESTART_EVENT);
}


SceneManager::~SceneManager() {
    this->clearList();
}


void SceneManager::loadArea(int area, int rooms) {
    std::string areaNo = std::to_string(area);
    // load in all rooms for this area
    for (int i = 1; i <= rooms; i++) {
        std::string roomNo = std::to_string(i);
        auto scene = std::make_shared<Scene>("area"s.append(areaNo).append("scene").append(roomNo));
        scene->scenePath = "./resources/Rebound/area"s
                               .append(areaNo).append("/room")
                               .append(roomNo).append("/room")
                               .append(roomNo).append("map.json");
        // add current scene to SceneManager's scenes
        this->addScene(scene);
    }
    // reset current room number to 1
    this->currRoom = 1;
}


void SceneManager::loadAllAreas(int areas) {
    // load all the areas into the linked list at once
    for (int a = 1; a <= areas; a++) {
        loadArea(a, this->numRooms[a-1]);
    }
}


void SceneManager::loadNewArea(int area, int rooms) { // not functioning correctly atm
    // std::string areaNo = std::to_string(area);
    // this->iter = this->head;
    // // set head and tail
    // for (int i = 1; i <= rooms; i++) {
    //     std::string roomNo = std::to_string(i);
    //     this->iter = this->iter->nextScene;
    //     if (this->iter == this->tail) {
    //         Scene* scene = new Scene("scene" + roomNo);
    //         scene->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
    //         // add current scene to SceneManager's scenes
    //         this->addScene(scene);
    //     }
    //     else {
    //         this->iter->scenePath = std::string("./resources/Rebound/area" + areaNo + "/room" + roomNo + "/room" + roomNo + "map.json");
    //     }
    // }
    // this->currRoom = 1;
}

void SceneManager::clearList() {
    this->iter = this->head->nextScene;
    while (this->iter->nextScene != nullptr) {
        this->deleteScene(this->iter->id);
        this->iter = this->iter->nextScene;
    }
    // set total room count = 0; no more room scenes in the list
    this->totalRoomsCount = 0;
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
    // we have one more room scene in the list
    this->totalRoomsCount++;
}


void SceneManager::deleteScene(std::string id) {
    this->iter = this->head;
    while (this->iter != this->tail) {
        if (this->iter->id == id) {
            // adjust pointers to accomodate deleted scene
            this->iter->prevScene->nextScene = this->iter->nextScene;
            this->iter->nextScene->prevScene = this->iter->prevScene;
            // we have one less room scene in the list
            this->totalRoomsCount--;
            // delete any remaining events
            if (EventDispatcher::getInstance().hasEventListener(iter.get(), NewSceneEvent::FADE_OUT_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter.get(), NewSceneEvent::FADE_OUT_EVENT);
	        }
            if (EventDispatcher::getInstance().hasEventListener(iter.get(), NewSceneEvent::FADE_IN_EVENT)) {
		        EventDispatcher::getInstance().removeEventListener(iter.get(), NewSceneEvent::FADE_IN_EVENT);
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
    // set area number of rooms based on rooms in current area
    this->areaRoomsCount = this->numRooms[this->currArea-1];

    // advance to next scene
    this->currScene = this->head->nextScene;
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;

    // load the first scene from the JSON file
    this->currScene->loadScene(this->currScene->scenePath);

    // load player info from scene object
    p->position = this->currScene->playerEntrancePos;
    p->width = p->height = 50;
    this->currScene->addChild(p);

    // load camera info from scene object
    // set camera limits - still need to do
    c->position = this->currScene->camEntrancePosition;
    c->pivot = this->currScene->camEntrancePivot;
    // set camera limits
    c->setTopLimit(this->currScene->camTopLimit);
	c->setLeftLimit(this->currScene->camLeftLimit);
	c->setRightLimit(this->currScene->camRightLimit);
    c->setBottomLimit(this->currScene->camBottomLimit);
    c->addChild(this->currScene);

    EventDispatcher::getInstance().addEventListener(this->currScene.get(), NewSceneEvent::FADE_OUT_EVENT);

}

void SceneManager::unloadScene() {
    // scene is done; queue fade out transition
    this->unloading = true;

    EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_OUT_EVENT));
    // Event will get auto-removed by DisplayObject
}

void SceneManager::loadNextScene() {
    // done w/ tween, this scene is no longer a child of camera
    this->currScene->removeThis();
    bool lol = false;

    // if at the end of the game, create new scene showing a game over message
    if (this->currScene->nextScene == this->tail) {
        auto s = std::make_shared<Scene>("hahahahaha");
        this->currScene = s;
        this->currScene->scenePath = "./resources/scene/game_win.json";
        lol = true;
    } else{
        // advance to next scene and increment current scene counter
        this->currScene = currScene->nextScene;
        this->currRoom++;
            // if done with this area, advance to next area
        if (this->currRoom > this->areaRoomsCount) {
            this->currArea++;
            // reset -- on first room of new area
            this->currRoom = 1;
            // set area number of rooms based on rooms in current area
            this->areaRoomsCount = numRooms[this->currArea - 1];
        }
    }
    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;

    // load the scene from JSON file
    this->currScene->loadScene(this->currScene->scenePath);

    // load player info from scene object
    p->position = this->currScene->playerEntrancePos;
    this->currScene->addChild(p);

    // load camera info from scene object
    // set camera limits - still need to do
    c->position = this->currScene->camEntrancePosition;
    c->pivot = this->currScene->camEntrancePivot;
    // set camera limits
    c->setTopLimit(this->currScene->camTopLimit);
	c->setLeftLimit(this->currScene->camLeftLimit);
	c->setRightLimit(this->currScene->camRightLimit);
    c->setBottomLimit(this->currScene->camBottomLimit);
    c->addChild(this->currScene);

    EventDispatcher::getInstance().addEventListener(this->currScene.get(), NewSceneEvent::FADE_OUT_EVENT);

    if (lol){
        auto text = std::make_shared<TextBox>("win", "Congrats? For winning, enjoy our version of the FFVII Remake!");
        text->position = {250, 200};
        this->currScene->addChild(text);
    }
}


void SceneManager::loadPrevScene() {
    // go back to previous scene and decrement current scene counter
    this->currScene = currScene->prevScene;
    this->currRoom--;

    // set player and camera
    this->currScene->player = p;
    this->currScene->camera = c;

    // load player info from scene object
    p->position = this->currScene->playerExitPos;
    this->currScene->addChild(p);

    // load camera info from scene object
    // set camera limits - still need to do
    c->position = this->currScene->camExitPosition;
    c->pivot = this->currScene->camExitPivot;
    this->c->printDisplayTree();
    // done w/ tween, this scene is no longer a child of camera
    this->c->removeImmediateChild(this->currScene->nextScene);
    std::cout << this->currScene->id << std::endl;
    c->addChild(this->currScene);
    std::cout << "----------------------------------------------" << std::endl;
    this->c->printDisplayTree();

}


void SceneManager::updateScene() {
    if (this->unloading) {
        return;
    }
    
    if (this->p->numOpponents > 0) {
        return;
    }

    // if forward condition is satisfied, transition to next scene
    if (this->currScene->forward_coord == "x" && this->currScene->forward_comp == ">") {
        if (this->p->position.x > this->currScene->goForward.x) {
            this->sceneChange = "next";
            this->p->removeThis();
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "x" && this->currScene->forward_comp == "<") {
        if (this->p->position.x < this->currScene->goForward.x) {
            this->sceneChange = "next";
            this->p->removeThis();
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "y" && this->currScene->forward_comp == ">") {
        if (this->p->position.y > this->currScene->goForward.y) {
            this->sceneChange = "next";
            this->p->removeThis();
            this->unloadScene();
            return;
        }
    }
    if (this->currScene->forward_coord == "y" && this->currScene->forward_comp == "<") {
        if (this->p->position.y < this->currScene->goForward.y) {
            this->sceneChange = "next";
            this->p->removeThis();
            this->unloadScene();
            return;
        }
    }

    

    // std::cout << "x" << std::endl;
    // std::cout << this->p->position.x << std::endl;
    // std::cout << "y" << std::endl;
    // std::cout << this->p->position.y << std::endl;

    // // if backward condition is satisfied, go back to previous scene
    // if (this->currScene->back_coord == "x" && this->currScene->back_comp == ">") {
    //     if (p->position.x > this->currScene->goBack.x) {
    //         if (this->currRoom > 1) {
    //             this->sceneChange = "previous";
    //             this->currScene->removeImmediateChild(p);
    //             this->unloadScene();
    //         }
    //         return;
    //     }
    // }
    // if (this->currScene->back_coord == "x" && this->currScene->back_comp == "<") {
    //     if (p->position.x < this->currScene->goBack.x) {
    //         if (this->currRoom > 1) {
    //             this->sceneChange = "previous";
    //             this->currScene->removeImmediateChild(p);
    //             this->unloadScene();
    //         }
    //         return;
    //     }
    // }
    // if (this->currScene->back_coord == "y" && this->currScene->back_comp == ">") {
    //     if (p->position.y < this->currScene->goBack.y) {
    //         if (this->currRoom > 1) {
    //             this->sceneChange = "previous";
    //             this->currScene->removeImmediateChild(p);
    //             this->unloadScene();
    //         }
    //         return;
    //     }
    // }
    // if (this->currScene->back_coord == "y" && this->currScene->back_comp == "<") {
    //     if (this->currRoom > 1) {
    //             this->sceneChange = "previous";
    //             this->currScene->removeImmediateChild(p);
    //             this->unloadScene();
    //         }
    //         return;
    // }
}


void SceneManager::handleEvent(Event* e) {
    if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT) {
        // fade out transition - load next scene once this scene transition is done
        if (((TweenEvent*) e)->getTween()->getID() == currScene->id + "_out_transition") {
            this->unloading = false;

            if (this->sceneChange == "previous") {
                this->loadPrevScene();
            }
            else {
                this->loadNextScene();
            }
            // queue scene transition
            EventDispatcher::getInstance().addEventListener(this->currScene.get(), NewSceneEvent::FADE_IN_EVENT);
            EventDispatcher::getInstance().dispatchEvent(new Event(NewSceneEvent::FADE_IN_EVENT));
            // Event will get auto-removed by DisplayObject
        }
    } else if(e->getType() == RestartEvent::RESTART_EVENT) {
        p->alive = true;
        this->currScene->removeThis();
        this->currScene = this->currScene->prevScene;
        this->currRoom--;
        this->loadNextScene();
        // this->currScene->addChild(p);
        //this->loadPrevScene();
        //this->loadNextScene();    
    }
}

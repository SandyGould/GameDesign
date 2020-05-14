#include "SceneManager.h"

#include "events/NewSceneEvent.h"
#include "events/RestartEvent.h"
#include "events/TweenEvent.h"

#include <iostream>

SceneManager::SceneManager(const shared_ptr<Camera>& camera, const shared_ptr<Player>& player) {
    this->p = player;
    this->c = camera;

    // add tween complete event for scene manager
    EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
    EventDispatcher::getInstance().addEventListener(this, RestartEvent::RESTART_EVENT);

    // update these two to set which room to start in (zero-indexed)
    // this->currArea = 2;
    // this->currRoom = 6;
}

void SceneManager::loadFirstScene() {
    // set area number of rooms based on rooms in current area
    this->areaRoomsCount = this->numRooms[this->currArea];

    // advance to next scene
    std::string areaNo = std::to_string(this->currArea + 1);
    std::string roomNo = std::to_string(this->currRoom + 1);
    this->currScene = make_shared<Scene>("area"s.append(areaNo).append("scene").append(roomNo));
    this->currScene->scenePath = "./resources/Rebound/area"s.append(areaNo)
        .append("/room").append(roomNo)
        .append("/room").append(roomNo).append("map.json");

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

    this->currRoom++;
    // if done with this area, advance to next area
    if (this->currRoom >= this->areaRoomsCount) {
        this->currArea++;
        // TODO: Don't hardcode this
        if (this->currArea >= 4) {
            lol = true;
        } else {
            this->currRoom = 0;
            this->areaRoomsCount = this->numRooms[this->currArea];
        }
    }

    if (!lol) {
        std::string areaNo = std::to_string(this->currArea + 1);
        std::string roomNo = std::to_string(this->currRoom + 1);
        this->currScene = make_shared<Scene>("area"s.append(areaNo).append("scene").append(roomNo));
        this->currScene->scenePath = "./resources/Rebound/area"s.append(areaNo)
            .append("/room").append(roomNo)
            .append("/room").append(roomNo).append("map.json");
    } else {
        // if at the end of the game, create new scene showing a game over message
        this->currScene = std::make_shared<Scene>("hahahahaha");
        this->currScene->scenePath = "./resources/scene/game_win.json";
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
    // this->currScene = currScene->prevScene;
    // this->currRoom--;
    //
    // // set player and camera
    // this->currScene->player = p;
    // this->currScene->camera = c;
    //
    // // load player info from scene object
    // p->position = this->currScene->playerExitPos;
    // this->currScene->addChild(p);
    //
    // // load camera info from scene object
    // // set camera limits - still need to do
    // c->position = this->currScene->camExitPosition;
    // c->pivot = this->currScene->camExitPivot;
    // this->c->printDisplayTree();
    // // done w/ tween, this scene is no longer a child of camera
    // this->c->removeImmediateChild(this->currScene->nextScene);
    // std::cout << this->currScene->id << std::endl;
    // c->addChild(this->currScene);
    // std::cout << "----------------------------------------------" << std::endl;
    // this->c->printDisplayTree();

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
        p->health = 100;
        p->alive = true;
        this->currRoom--;
        this->loadNextScene();
    }
}

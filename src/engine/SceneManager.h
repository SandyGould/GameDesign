#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "Camera.h"
#include "things/Player.h"
#include "events/EventListener.h"
#include "events/Event.h"
#include "CollisionSystem.h"
#include "things/TextBox.h"

#include <list>

class SceneManager : public EventListener, public std::enable_shared_from_this<SceneManager>  { 

    public:
        SceneManager(shared_ptr<Camera>c, shared_ptr<Player> p);
	    ~SceneManager();
        void loadArea(int area, int rooms);
        void loadAllAreas(int areas);
        void loadNewArea(int area, int rooms);
        void clearArea();
        shared_ptr<Scene> findScene(std::string id);
        void addScene(shared_ptr<Scene> scene);
        void deleteScene(std::string id);
        void unloadScene();
        void loadFirstScene();
        void loadNextScene();
        void loadPrevScene();

        void updateScene();

        void handleEvent(Event* e) override;

        shared_ptr<Scene> currScene;

    private:
        shared_ptr<Player> p;
        shared_ptr<Camera> c;

        shared_ptr<CollisionSystem> collisionSystem;
        
        std::string sceneChange = std::string("");

        shared_ptr<Scene> head;
        shared_ptr<Scene> tail;
        shared_ptr<Scene> iter;

        shared_ptr<TextBox> new_area_text;

        // miscellaneous things to keep track of
        int roomsCount = 0;
        int currRoom = 1;
        int currArea = 1;

        int numRooms[4] = {3,2,3,7};
        
};

#endif
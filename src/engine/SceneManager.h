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

class SceneManager : public EventListener  { 

    public:
        SceneManager(Camera* c, Player* p);
	    ~SceneManager();
        void loadArea(int area, int rooms);
        void loadAllAreas(int areas);
        void loadNewArea(int area, int rooms);
        void clearList();
        Scene* findScene(std::string id);
        void addScene(Scene* scene);
        void deleteScene(std::string id);
        void unloadScene();
        void loadFirstScene();
        void loadNextScene();
        void loadPrevScene();

        void updateScene();

        void handleEvent(Event* e) override;

        Scene* currScene;

    private:
        Player* p;
        Camera* c;

        CollisionSystem* collisionSystem;
        
        std::string sceneChange = std::string("");

        Scene* head;
        Scene* tail;
        Scene* iter;

        TextBox* new_area_text;

        // miscellaneous things to keep track of
        int totalRoomsCount = 0;
        int areaRoomsCount = 0;
        int currRoom = 1;
        int currArea = 1;

        int numRooms[4] = {3,2,3,7};
        
};

#endif
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "Camera.h"
#include "things/Player.h"
#include "events/EventListener.h"
#include "events/Event.h"
#include "things/TextBox.h"

#include <list>

class SceneManager : public EventListener {

    public:
        SceneManager(shared_ptr<Camera>c, shared_ptr<Player> p);
	    ~SceneManager();
        void loadArea(int area, int rooms);
        void loadAllAreas(int areas);
        void loadNewArea(int area, int rooms);
        void clearList();
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
        
        std::string sceneChange = std::string("");

        shared_ptr<Scene> head;
        shared_ptr<Scene> tail;
        shared_ptr<Scene> iter;

        shared_ptr<TextBox> new_area_text;

        // miscellaneous things to keep track of
        int totalRoomsCount = 0;
        int areaRoomsCount = 0;
        int currRoom = 1;
        int currArea = 1;

        int numRooms[4] = {3,8,8,7};
        
};

#endif
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
        SceneManager(const shared_ptr<Camera>& camera, const shared_ptr<Player>& player);

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

        shared_ptr<TextBox> new_area_text;

        bool unloading = false;

        // miscellaneous things to keep track of
        int areaRoomsCount = 0;
        int currRoom = 0;
        int currArea = 0;

        int numRooms[4] = {8,8,8,8};
        
};

#endif
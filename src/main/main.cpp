#include "Editor.h"
#include "Rebound.h"
#include "Rooms.h"
#include "demos/CollisionDemo.h"
#include "demos/LoadSceneDemo.h"

#include <iostream>
#include <string>

// SDL tries to redefine main? Need to investigate later
#undef main

using namespace std;

int main(int argc, char** argv) {
    if (argc > 3) {
        cout << "Unrecognized arguments, launching game." << endl;
        Rebound().start();
    } else if (argc > 1) {
        string arg(argv[1]);
        if (arg == "demo") {
            if (argc == 3) {
                string demo(argv[2]);
                if (demo == "collision") {
                    CollisionDemo().start();
                } else if (demo == "load_scene") {
                    LoadSceneDemo().start();
                } else {
                    cout << "Unknown demo!" << endl;
                }
            }
        } else if (arg == "editor") {
            if (argc == 3) {
                string scene(argv[2]);
                Editor(scene).start();
            } else {
                Editor().start();
            }
        } else if (arg == "sfx_demo") {
            Rooms().start();
        } else {
            cout << "Unrecognized arguments, launching game." << endl;
            Rebound().start();
        }
    } else {
        Rooms().start();
        // Rebound* rebound = new Rebound();
        // rebound->start();
    }

    return 0;
}

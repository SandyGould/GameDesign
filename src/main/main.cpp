#include "Editor.h"
#include "Rebound.h"
#include "demos/CollisionDemo.h"

#include <iostream>
#include <string>

// SDL tries to redefine main? Need to investigate later
#undef main

using namespace std;

int main(int argc, char** argv) {
	if (argc > 3) {
		cout << "Unrecognized arguments, launching game." << endl;
		Rebound* rebound = new Rebound();
		rebound->start();
	} else if (argc > 1){
		string arg(argv[1]);
		if (arg == "demo") {
			if (argc == 3) {
                string demo(argv[2]);
                if (demo == "collision") {
                    CollisionDemo* demo = new CollisionDemo();
                    demo->start();
                } else {
                    cout << "Unknown demo!" << endl;
                }
            }
		} else if (arg == "editor") {
			Editor* editor;
			if (argc == 3) {
				string scene(argv[2]);
				editor = new Editor(scene);
			} else {
				editor = new Editor();
			}
			editor->start();
		} else {
            cout << "Unrecognized arguments, launching game." << endl;
            Rebound* rebound = new Rebound();
            rebound->start();
        }
	} else {
		Rebound* rebound = new Rebound();
		rebound->start();
	}

	return 0;
}

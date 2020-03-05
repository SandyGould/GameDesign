#include "Rebound.h"
#include "Editor.h"

#include <string>
#include <iostream>

// SDL tries to redefine main? Need to investigate later
#undef main

using namespace std;

int main(int argc, char** argv) {
	if (argc > 3) {
		cout << "Unrecognized arguments, launching game." << endl;
		Rebound* rebound = new Rebound();
		rebound->start();
	} else if (argc > 1){
		string edit(argv[1]);
		if (edit != "editor"){
			cout << "Unrecognized arguments, launching game." << endl;
			Rebound* rebound = new Rebound();
			rebound->start();
		} else{
			Editor* editor;
			if (argc == 3){
				string scene(argv[2]);
				editor = new Editor(scene);
			} else{
				editor = new Editor();
			}
			editor->start();
		}
	} else {
		Rebound* rebound = new Rebound();
		rebound->start();
	}

	return 0;
}

#include "MyGame.h"
#include "Editor.h"

#include <string>

// SDL tries to redefine main? Need to investigate later
#undef main

using namespace std;

int main(int argc, char** argv) {
	if (argc == 2) {
		string scene(argv[1]);
		Editor editor(scene);
		editor.start();
	} else {
		MyGame myGame;
		myGame.start();
	}

	return 0;
}

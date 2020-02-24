#include "MyGame.h"

#include <string>

// SDL tries to redefine main? Need to investigate later
#undef main

using namespace std;

int main(int argc, char** argv) {
	MyGame* myGame;
	if (argc == 2){
		string scene = argv[1];
		myGame = new MyGame(scene);
	} else{
		myGame = new MyGame();
	}

	myGame->start();
	return 0;
}

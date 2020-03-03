#include "MyGame.h"


// SDL tries to redefine main? Need to investigate later
#undef main

int main(int argc, char** argv) {
	MyGame myGame{};
	myGame.start();
	return 0;
}

#include "MyGame.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main(int argc, char** argv) {
	MyGame myGame{};
	myGame.start();
	return 0;
}

#ifdef _WIN32
#include <windows.h>

#ifdef __GNUC__
#define _stdcall  __attribute__((stdcall))
#endif

int _stdcall
WinMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPSTR lpszCmdLine,
		_In_ int nCmdShow) {
	return main(__argc, __argv);
}
#endif

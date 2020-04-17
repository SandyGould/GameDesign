#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

class Sound{ 

public:
	Sound();
	~Sound();

	void setSFX(std::string filename);
	void setMusic(std::string filename);

	// One time play
	void playSFX();
	// Repeated play
	void playMusic();

	void pauseMusic();

	void quitSounds();

private:
	Mix_Music *music;
	Mix_Chunk *sfx;
	
};

#endif
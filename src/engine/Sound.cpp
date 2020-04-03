#include "Sound.h"
#include <iostream>

Sound::Sound(){
	int audio_rate = MIX_DEFAULT_FREQUENCY;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = MIX_DEFAULT_CHANNELS;
	int audio_buffers=512;

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)){
		std::cout << "Unable to open audio: " << Mix_GetError() << std::endl;
	}

	music = NULL;
	sfx = NULL;
}

Sound::~Sound(){
	Mix_FreeMusic(music);
	music = NULL;
	Mix_FreeChunk(sfx);
	sfx = NULL;
}

void Sound::setSFX(std::string filename){
	sfx = Mix_LoadWAV(filename.c_str());
	if (sfx == NULL)
		std::cout << "Error loading SFX: " << Mix_GetError() << std::endl;
}

void Sound::setMusic(std::string filename){
	music = Mix_LoadMUS(filename.c_str());
	if(music == NULL)
		std::cout << "Error loading music: " << Mix_GetError() << std::endl;
}

void Sound::playSFX(){
	if(Mix_PlayChannel(-1, sfx, 0) < 0)
		std::cout << "Could not play SFX" << std::endl;
}

void Sound::playMusic(){
	if(Mix_PlayMusic(music, -1) < 0)
		std::cout << "Could not play Music" << std::endl;
}

void Sound::pauseMusic(){
	Mix_PauseMusic();
}

void Sound::quitSounds(){
	Mix_Quit();
}
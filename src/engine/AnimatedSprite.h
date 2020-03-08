#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>

struct Frame {
	SDL_Surface* image;
	SDL_Texture* texture;
};

struct Animation {
	Frame** frames;
	std::string animName;
	int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
	std::string basepath;
};

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string id);
	~AnimatedSprite() override;

	void addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(std::string animName);

	void play(std::string animName);
	void replay();
	void stop();

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

	bool playing = false;

	std::vector<Animation*> animations;
	Animation* current;

private:
	int frameCount;
};

#endif

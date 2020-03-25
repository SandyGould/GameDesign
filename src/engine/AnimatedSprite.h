#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>
#include <utility>

struct Frame {
	//SDL_Surface* image;
	//SDL_Texture* texture;
	//SDL_Rect source;
	int x;
	int y;
	int w;
	int h;
};

struct Animation {
	SDL_Rect ** frames;
	std::string animName;
	int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
};


class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(std::string id);
	AnimatedSprite(std::string id, std::string spritesheet, std::string xml);
	~AnimatedSprite();

	void addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop);
	void spritesheetAnimation(std::string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(std::string animName);

	void play(std::string animName);
	void replay();
	void stop();

	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);
	bool playing = false;
	bool useSheet = false;
	void parse(std::string xml);
	    std::vector<std::pair<int,int>> xy;
	std::string sheetpath;
	std::vector<Animation*> animations;
	SDL_Surface* image;
	SDL_Texture* texture;
	//SDL_Rect source;

private:
	Animation* current;
	
	int frameCount;
	
	
};

#endif

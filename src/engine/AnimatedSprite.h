#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "Game.h"

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
	std::string basepath;
};

struct sheetAnim{
	SDL_Surface* sheet_surface;
	SDL_Texture* sheet_texture;
};

struct sheetFrame{

};


class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string id, SDL_Renderer* r);
	AnimatedSprite(std::string id, std::string spritesheet, std::string xml);
	AnimatedSprite(std::string id, std::string spritesheet, std::string xml, SDL_Renderer* r);
	AnimatedSprite(const DisplayObject& other);
	~AnimatedSprite();

	void addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop);
	void spritesheetAnimation(std::string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(std::string animName);

	void play(int index);
	void play(std::string animName);
	void replay();
	void stop();

	void draw(AffineTransform& at) override;
	void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL) override;

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;

	bool playing = false;
	bool useSheet = false;
	void parse(std::string xml);
	std::vector<std::pair<int,int>> xy;
	std::string sheetpath;
	std::string xmlpath;
	std::vector<Animation*> animations;
	SDL_Surface* image;
	SDL_Texture* texture;
	//SDL_Rect source;

	Animation* current;

private:
	
	
	int frameCount;
	
	
};

#endif

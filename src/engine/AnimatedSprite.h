#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "Game.h"

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

struct sheetAnim{
	SDL_Surface* sheet_surface;
	SDL_Texture* sheet_texture;
};

struct sheetFrame{

};

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string id, SDL_Renderer *r = Game::renderer);
	AnimatedSprite(std::string id, std::string spritesheet, std::string sheet_anims, SDL_Renderer *r = Game::renderer);
	~AnimatedSprite();

	void addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop, SDL_Renderer *r = Game::renderer);
	Animation* getAnimation(std::string animName);

	void play(std::string animName);
	void replay();
	void stop();

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);
	virtual void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL);

	bool playing = false;

	std::vector<Animation*> animations;
	std::vector<Animation*> sheetAnimations;
	Animation* current;
	sheetAnim* curSheetAnim;

private:
	int frameCount;
	bool isSheet = false;
};

#endif

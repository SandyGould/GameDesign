#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Game.h"
#include "Sprite.h"
#include "pugixml.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <utility>
#include <vector>

struct Animation {
    std::vector<SDL_Rect> frames;
	std::string animName;
	int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
};

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(std::string id, std::string spritesheet, std::string xml, SDL_Renderer* r = Game::renderer);
	explicit AnimatedSprite(const DisplayObject& other);

	Animation getAnimation(std::string animName);

	void play(int index);
	void play(std::string animName);
	void replay();
	void stop();

	void draw(AffineTransform& at) override;

	void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

	bool playing = false;
	void parse(std::string xml);
	std::string xmlpath;
	std::vector<Animation> animations;

	Animation current;

private:
    static std::unordered_map<std::string, std::vector<Animation>> spritesheets;

	int frameCount;
};

#endif

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
    AnimatedSprite(const std::string& id,
                   const std::string& spritesheet,
                   const std::string& xml,
                   const std::string& animName,
                   SDL_Renderer* r = Game::renderer);
    explicit AnimatedSprite(const DisplayObject& other);

    Animation getAnimation(const std::string& animName);

    void play(const std::string& animName);
    void replay();
    void stop();

    void draw(AffineTransform& at) override;
    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;

    std::string xmlpath;

    Animation current;

private:
    static void parse(const std::string& xml);

    static std::unordered_map<std::string, std::vector<Animation>> spritesheets;

    bool playing = false;
    std::vector<Animation> animations;

    int frameCount;
};

#endif

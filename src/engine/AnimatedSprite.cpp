#include "AnimatedSprite.h"

#include "json.hpp"
#include "pugixml.hpp"

#include <fstream>

using namespace std::string_literals;
using json = nlohmann::json;

std::unordered_map<std::string, std::vector<Animation>> AnimatedSprite::spritesheets;

AnimatedSprite::AnimatedSprite(std::string id, std::string spritesheet, std::string xml, SDL_Renderer* r)
    : Sprite(id, spritesheet, r) {
    this->type = "AnimatedSprite";
    this->saveType = this->type;
    this->renderer = r;
    this->xmlpath = xml;

    if (AnimatedSprite::spritesheets.find(xml) == AnimatedSprite::spritesheets.cend()) {
        this->parse(this->xmlpath);
    }

    this->animations = AnimatedSprite::spritesheets.at(xml);
    if (!this->animations.empty()) {
        this->play(0);
    }
}

AnimatedSprite::AnimatedSprite(const DisplayObject& other)
    : Sprite(other.id) {
    if (other.type == "AnimatedSprite") {
        AnimatedSprite* AS = (AnimatedSprite*)&other;
        this->id = AS->id + "_copy";
        this->type = AS->type;
        this->saveType = AS->saveType;
        this->renderer = AS->renderer;
        this->xmlpath = AS->xmlpath;
        this->width = AS->width;
        this->height = AS->height;
        this->visible = AS->visible;
        this->pivot = AS->pivot;
        this->scaleX = AS->scaleX;
        this->scaleY = AS->scaleY;
        this->rotation = AS->rotation;
        this->facingRight = AS->facingRight;
        this->hasCollision = AS->hasCollision;
        if (AnimatedSprite::spritesheets.find(this->xmlpath) == AnimatedSprite::spritesheets.cend()) {
            parse(this->xmlpath);
        }
        this->imgPath = other.imgPath;
        this->loadTexture(this->imgPath);
    } else {
        this->type = "AnimatedSprite";
        this->id = "FAILED_COPY";
        this->renderer = Game::renderer;
    }

    this->animations = AnimatedSprite::spritesheets.at(this->xmlpath);
    if (!this->animations.empty()) {
        this->play(0);
    }
}

void AnimatedSprite::parse(std::string xml) {
    //for more information about this library look here https://stackoverflow.com/questions/39067300/c-parsing-sub-nodes-of-xml
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml.c_str());

    std::vector<Animation> animations;

    for (auto& anim : doc.child("TextureAtlas")) {
        Animation newanim{
            std::vector<SDL_Rect>(anim.attribute("numFrames").as_int()),
            anim.attribute("name").as_string(),
            anim.attribute("numFrames").as_int(),
            anim.attribute("frameRate").as_int(),
            anim.attribute("loop").as_string() == "true"s, // force "true" to be a std::string
            0,
        };

        int framenum = 0;
        for (auto frame : anim) {
            newanim.frames[framenum].x = frame.attribute("x").as_int();
            newanim.frames[framenum].y = frame.attribute("y").as_int();
            newanim.frames[framenum].w = frame.attribute("w").as_int();
            newanim.frames[framenum].h = frame.attribute("h").as_int();
            framenum++;
        }
        animations.push_back(newanim);
    }

    AnimatedSprite::spritesheets.try_emplace(xml, animations);
}

Animation AnimatedSprite::getAnimation(std::string animName) {
    for (auto animation : this->animations) {
        if (animation.animName == animName) {
            return animation;
        }
    }

    return {
        {},
        "INVALID_ANIMATION",
        0,
        0,
        false,
        0,
    };
}

void AnimatedSprite::play(int index) {
    if (index < this->animations.size()) {
        Animation anim = this->animations[index];
        this->current = anim;
        this->current.curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::play(std::string animName) {
    Animation anim = getAnimation(animName);
    if (anim.animName == "INVALID_ANIMATION") {
        return;
    }

    this->current = anim;
    this->current.curFrame = 0;
    frameCount = 0;
    playing = true;
}

void AnimatedSprite::replay() {
    current.curFrame = 0;
    frameCount = 0;
    playing = true;
}

void AnimatedSprite::stop() {
    this->playing = false;
}

void AnimatedSprite::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
    if (playing) {
        frameCount++;
        if (frameCount % current.frameRate == 0) {
            // increment local frame counter
            current.curFrame++;
            // check for array out of bounds
            if (current.curFrame == current.numFrames - 1) {
                // check for looping, reset if looping
                if (!current.loop) {
                    stop();
                } else {
                    current.curFrame = 0;
                }
            }

            //We update the location of the image each frame
            this->updateSourceRect(&current.frames[current.curFrame]);
        }
    }
}

void AnimatedSprite::draw(AffineTransform& at) {
    Sprite::draw(at);
}

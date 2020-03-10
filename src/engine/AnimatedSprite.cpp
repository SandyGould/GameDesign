#include "AnimatedSprite.h"
#include "Game.h"
#include "pugixml.hpp"
#include <fstream>

AnimatedSprite::AnimatedSprite() : Sprite() {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(std::string id) : Sprite(id, 0, 0, 0) {
    this->type = "AnimatedSprite";
}

//Spritesheet constructor
AnimatedSprite::AnimatedSprite(std::string id, std::string spritesheet, std::string xml) : Sprite(id, spritesheet){
    this->type = "AnimatedSprite";
    parse(xml);
}

void AnimatedSprite::parse(std::string xml){
    //for more information about this library look here https://stackoverflow.com/questions/39067300/c-parsing-sub-nodes-of-xml
    int x;
    int y;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml.c_str());
    for(auto sprite: doc.child("TextureAtlas").child("Sprite")){
        x = sprite.attribute("x").as_int();
        y = sprite.attribute("y").as_int();
        std::pair<int,int> newPair(x,y);
        xy.push_back(newPair);
    }
}


AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            if (an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
            if (an->frames[i]->texture != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop) {
    Animation* anim = new Animation{
        new Frame * [numFrames], // new frame pointer array of size numFrames;
        animName,
        numFrames,
        frameRate,
        loop,
        0,
    };
    for (int i = 0; i < numFrames; i++) {
        Frame* f = new Frame();
        std::string path = basepath + animName + "_" + std::to_string(i + 1) + ".png";
        f->image = IMG_Load(path.c_str());
        f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        anim->frames[i] = f;
    }
    animations.push_back(anim);
}

void AnimatedSprite::spritesheetAnimation(std::string animName, int numFrames, int frameRate, bool loop){
    Animation* anim = new Animation{
        new Frame * [numFrames], // new frame pointer array of size numFrames;
        animName,
        numFrames,
        frameRate,
        loop,
        0,
    };
    useSheet = true;
    SDL_Rect frameSource = {0,0,416,454};
    for(int i = 0; i< numFrames; i++){
        Frame* f = new Frame();
        frameSource.x = xy[i].first;
        frameSource.y = xy[i].second;
        f->source = frameSource;
        anim->frames[i] = f;
    }
    
}

Animation* AnimatedSprite::getAnimation(std::string animName) {
    for (auto animation : animations) {
        if (animation->animName == animName) {
            return animation;
        }
    }
    return nullptr;
}

void AnimatedSprite::play(std::string animName) {
    Animation* anim = getAnimation(animName);
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::replay() {
    if (this->current != NULL) {
        current->curFrame = 0;
        frameCount = 0;
        playing = true;
    }
}

void AnimatedSprite::stop() {
    this->playing = false;
}

void AnimatedSprite::update(std::set<SDL_Scancode> pressedKeys) {
    Sprite::update(pressedKeys);
    if (playing) {
        frameCount++;
        if (frameCount % current->frameRate == 0) {
            // increment local frame counter
            current->curFrame++;
            // check for array out of bounds
            if (current->curFrame == current->numFrames) {
                // reset the animation
                current->curFrame = 0;
                // check for looping
                if (!current->loop) {
                    stop();
                }
            }
            //We update the location of the image each frame
            if(useSheet){
                sourceRect = current->frames[current->curFrame]->source;
            }
            else{
                DisplayObject::setTexture(current->frames[current->curFrame]->texture);
            }
        }

    }
    
}

void AnimatedSprite::draw(AffineTransform& at) {
    Sprite::draw(at);
}
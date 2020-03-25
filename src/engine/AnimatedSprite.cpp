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
    this->sheetpath = spritesheet;
    parse(xml);
}

void AnimatedSprite::parse(std::string xml){
    //for more information about this library look here https://stackoverflow.com/questions/39067300/c-parsing-sub-nodes-of-xml
    int x;
    int y;
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml.c_str());
    image = new SDL_Surface;
    image = IMG_Load(sheetpath.c_str());
    //texture = new SDL_Texture;
    texture = SDL_CreateTextureFromSurface(Game::renderer,image);

    
    for(auto anim: doc.child("TextureAtlas")){
        printf("On XML for anim %s\n", anim.attribute("name").as_string());
        Animation* newanim = new Animation{ 
        new SDL_Rect * [anim.attribute("numFrames").as_int()], // new frame pointer array of size numFrames;
        anim.attribute("name").as_string(),
        anim.attribute("numFrames").as_int(),
        anim.attribute("frameRate").as_int(),
        strcasecmp((anim.attribute("loop")).as_string(), "true") == 0,
        0,
    };
        int framenum = 0;
        for(auto sprite:anim)
        {
            //std::pair<int,int> newPair(sprite.attribute("x").as_int(),sprite.attribute("y").as_int());
            printf("On sprite %s\n", sprite.attribute("n").as_string());
            SDL_Rect* f = new SDL_Rect();
            f->x = sprite.attribute("x").as_int();
            f->y = sprite.attribute("y").as_int();
            f->w = sprite.attribute("w").as_int();
            f->h = sprite.attribute("h").as_int();
            //f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
            newanim->frames[framenum] = f;
            printf("%d %d\n", f->x, f->y);
            framenum++;
             
        //std::pair<int,int> newPair(x,y);
        //xy.push_back(newPair); 
        }
        animations.push_back(newanim);
        //attribute n = name
        //string s_name = sprite.attribute("n");
       
    }
    useSheet = true;
}


AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            //if (an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
            //if (an->frames[i]->texture != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(std::string basepath, std::string animName, int numFrames, int frameRate, bool loop) {
//    Animation* anim = new Animation{
//        new Frame * [numFrames], // new frame pointer array of size numFrames;
//        animName,
 //       numFrames,
  //      frameRate,
   //     loop,
    //    0,
    //};
    //for (int i = 0; i < numFrames; i++) {
     //   Frame* f = new Frame();
      //  std::string path = basepath + animName + "_" + std::to_string(i + 1) + ".png";
       // f->image = IMG_Load(path.c_str());
        //f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        //anim->frames[i] = f;
    //}
    //animations.push_back(anim);
}

void AnimatedSprite::spritesheetAnimation(std::string animName, int numFrames, int frameRate, bool loop){
    //Animation* anim = new Animation{
     //   new Frame * [numFrames], // new frame pointer array of size numFrames;
      //  animName,
       // numFrames,
        //frameRate,
        //loop,
        //0,
    //};
    //useSheet = true;
    //SDL_Rect frameSource = {0,0,416,454};
    //for(int i = 0; i< numFrames; i++){
      //  Frame* f = new Frame();
        //frameSource.x = xy[i].first;
        //frameSource.y = xy[i].second;
        //f->source = frameSource;
        //anim->frames[i] = f;
   // }
    
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
    printf("Searching for animation %s\n",animName.c_str());
    Animation* anim = getAnimation(animName);
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
       printf("Playing anim\n");
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

void AnimatedSprite::update(std::set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
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
                //sourceRect = current->frames[current->curFrame];
                this->DisplayObject::updateSourceRect(current->frames[current->curFrame]);
                printf("Update source called %d %d\n", current->frames[current->curFrame]->x,current->frames[current->curFrame]->y);
            }
            else{
                //DisplayObject::setTexture(current->frames[current->curFrame]->texture);
            }
        }

    }
    
}

void AnimatedSprite::draw(AffineTransform& at) {
    Sprite::draw(at);
}
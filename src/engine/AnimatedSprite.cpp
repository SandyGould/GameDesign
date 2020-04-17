#include "AnimatedSprite.h"
#include "json.hpp"
#include "pugixml.hpp"
#include <fstream>

using namespace std::string_literals;
using json = nlohmann::json;

AnimatedSprite::AnimatedSprite(std::string id, SDL_Renderer *r) : Sprite(id) {
    this->type = "AnimatedSprite";
    this->saveType = this->type;
    this->renderer = r;
}

//Spritesheet constructors
AnimatedSprite::AnimatedSprite(std::string id, std::string spritesheet, std::string xml) : AnimatedSprite(id, spritesheet, xml, Game::renderer){

}

AnimatedSprite::AnimatedSprite(std::string id, std::string spritesheet, std::string xml, SDL_Renderer* r) : Sprite(id, spritesheet, r){
    this->type = "AnimatedSprite";
    this->saveType = this->type;
    this->sheetpath = spritesheet;
    this->renderer = r;
    this->xmlpath = xml;
    this->visible = true;
    parse(this->xmlpath);
    if (!animations.empty()){
        this->play(0);
    }
}

AnimatedSprite::AnimatedSprite(const DisplayObject& other) : Sprite(other.id){
    if (other.type == "AnimatedSprite"){
        AnimatedSprite* AS = (AnimatedSprite*) &other;
        this->id = AS->id + "_copy";
        this->type = AS->type;
        this->saveType = AS->saveType;
        this->sheetpath = AS->sheetpath;
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
        parse(this->xmlpath);
        this->imgPath = other.imgPath;
        this->loadTexture(this->imgPath, Game::renderer);
    } else{
        this->type = "AnimatedSprite";
        this->id = "FAILED_COPY";
        this->renderer = Game::renderer;
    }
    if (!animations.empty()){
        this->play(0);
    }
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
    texture = SDL_CreateTextureFromSurface(renderer,image);

    for(auto& anim: doc.child("TextureAtlas")){
        //printf("On XML for anim %s\n", anim.attribute("name").as_string());
        Animation* newanim = new Animation{ 
            new SDL_Rect * [anim.attribute("numFrames").as_int()], // new frame pointer array of size numFrames;
            anim.attribute("name").as_string(),
            anim.attribute("numFrames").as_int(),
            anim.attribute("frameRate").as_int(),
            anim.attribute("loop").as_string() == "true"s, // force "true" to be a std::string
            0,
        };
        int framenum = 0;
        for(auto sprite:anim)
        {
            //std::pair<int,int> newPair(sprite.attribute("x").as_int(),sprite.attribute("y").as_int());
            //printf("On sprite %s\n", sprite.attribute("n").as_string());
            SDL_Rect* f = new SDL_Rect();
            f->x = sprite.attribute("x").as_int();
            f->y = sprite.attribute("y").as_int();
            f->w = sprite.attribute("w").as_int();
            f->h = sprite.attribute("h").as_int();
            //f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
            newanim->frames[framenum] = f;
            //printf("%d %d\n", f->x, f->y);
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

void AnimatedSprite::play(int index) {
    Animation* anim = NULL;
    if (index < animations.size()){
        anim = animations[index];
    }
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
       //printf("Playing anim\n");
    }
}

void AnimatedSprite::play(std::string animName) {
    //printf("Searching for animation %s\n",animName.c_str());
    Animation* anim = getAnimation(animName);
    if (anim != NULL) {
        this->current = anim;
        this->current->curFrame = 0;
        frameCount = 0;
        playing = true;
       //printf("Playing anim\n");
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

void AnimatedSprite::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    Sprite::update(pressedKeys, joystickState, pressedButtons);
    if (playing) {
        frameCount++;
        if (frameCount % current->frameRate == 0) {
            // increment local frame counter
            current->curFrame++;
            // check for array out of bounds
            if (current->curFrame == current->numFrames - 1) {
                // check for looping, reset if looping
                if (!current->loop) {
                    stop();
                } else{
                    current->curFrame = 0;
                }
            }
            //We update the location of the image each frame
            if(useSheet){
                //sourceRect = current->frames[current->curFrame];
                this->DisplayObject::updateSourceRect(current->frames[current->curFrame]);
                //printf("Update source called %d %d\n", current->frames[current->curFrame]->x,current->frames[current->curFrame]->y);
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
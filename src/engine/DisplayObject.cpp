#include "DisplayObject.h"

#include "Game.h"
#include "events/DisplayTreeChangeEvent.h"

#include <algorithm>
#include <cmath>
#include <iostream>

DisplayObject::DisplayObject(std::string id) {
    this->id = id;

    this->renderer = Game::renderer;

    this->image = NULL;
    this->texture = NULL;
    this->curTexture = NULL;
}

DisplayObject::DisplayObject(std::string id, std::string filepath)
    : DisplayObject(id) {
    this->imgPath = filepath;

    loadTexture(filepath, Game::renderer);
}

DisplayObject::DisplayObject(std::string id, std::string filepath, SDL_Renderer* r)
    : DisplayObject(id) {
    this->imgPath = filepath;
    this->renderer = r;

    loadTexture(filepath, r);
}

DisplayObject::DisplayObject(std::string id, int red, int green, int blue)
    : DisplayObject(id, red, green, blue, 100, 100) {
}

DisplayObject::DisplayObject(std::string id, int red, int green, int blue, int width, int height)
    : DisplayObject(id, red, green, blue, width, height, Game::renderer) {
}

DisplayObject::DisplayObject(std::string id, int red, int green, int blue, int width, int height, SDL_Renderer* r)
    : DisplayObject(id) {
    this->id = id;

    this->red = red;
    this->blue = blue;
    this->green = green;

    this->width = width;
    this->height = height;

    this->renderer = r;

    this->loadRGBTexture(red, green, blue, width, height, r);
}

DisplayObject::DisplayObject(const DisplayObject& other) {
    this->position = other.position;
    this->width = other.width;
    this->height = other.height;
    this->pivot = other.pivot;
    this->scaleX = other.scaleX;
    this->scaleY = other.scaleY;
    this->rotation = other.rotation; // in radians
    this->facingRight = other.facingRight;
    this->hasCollision = other.hasCollision;
    // copy(static_cast<DisplayObjectContainer*>(other)->children.begin(),
    // (static_cast<DisplayObjectContainer*>(other)->children.end()),
    // back_inserter((static_cast<DisplayObjectContainer*>(this)->children)));
    // copy(static_cast<DisplayObjectContainer*>(other)->collisionList.begin(),
    // static_cast<DisplayObjectContainer*>(other)->collisionList.end(),
    // back_inserter(static_cast<DisplayObjectContainer*>(this)->collisionList));
    this->id = other.id + "_copy";
    this->imgPath = other.imgPath;
    this->loadTexture(this->imgPath, Game::renderer);
}

DisplayObject::~DisplayObject() {
    //TODO: Get this freeing working
    if (image != NULL) {
        SDL_FreeSurface(image);
    }

    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }

    for (auto* child : children) {
        delete child;
    }
}

void DisplayObject::loadTexture(std::string filepath, SDL_Renderer* r) {
    image = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(r, image);
    setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue, int width, int height, SDL_Renderer* r) {
    image = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0x000000ff);
    SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
    texture = SDL_CreateTextureFromSurface(r, image);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    setTexture(texture);
}

SDL_Point DisplayObject::getGlobalPosition() {
    DisplayObject* parent = this->parent;
    std::vector<DisplayObject*> parentList;
    while (parent != NULL) {
        parentList.push_back(parent);
        parent = parent->parent;
    }

    AffineTransform at;
    for (auto i = parentList.rbegin(); i != parentList.rend(); ++i) {
        (*i)->applyTransformations(at);
        if ((*i)->type != "Camera") {
            at.translate((*i)->pivot.x, (*i)->pivot.y);
        }
    }

    applyTransformations(at);
    SDL_Point origin = at.transformPoint(0, 0);
    reverseTransformations(at);

    for (auto i = parentList.begin(); i != parentList.end(); ++i) {
        if ((*i)->type != "Camera") {
            at.translate(-(*i)->pivot.x, -(*i)->pivot.y);
        }
        (*i)->reverseTransformations(at);
    }
    return origin;
}

void DisplayObject::setTexture(SDL_Texture* t) {
    this->curTexture = t;
}

void DisplayObject::addChild(DisplayObject* child) {
    if (child->parent != this) {
        children.push_back(child);
        child->parent = this; // make sure to include reverse reference also
        child->parentId = id;

        DisplayTreeChangeEvent* event = new DisplayTreeChangeEvent(child, true);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;
    }
}

void DisplayObject::removeImmediateChild(DisplayObject* child) {
    auto it = std::find(this->children.cbegin(), this->children.cend(), child);
    if (it != this->children.cend()) {
        DisplayTreeChangeEvent* event = new DisplayTreeChangeEvent(*it, false);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        delete *it;
        this->children.erase(it);
    }
}

void DisplayObject::removeImmediateChild(std::string id) {
    auto it = std::find_if(this->children.cbegin(), this->children.cend(), [&](const auto child) { return child->id == id; });
    if (it != this->children.cend()) {
        DisplayTreeChangeEvent* event = new DisplayTreeChangeEvent(*it, true);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        delete *it;
        this->children.erase(it);
    }
}

void DisplayObject::removeChild(size_t index) {
    if (index < children.size()) {
        DisplayTreeChangeEvent* event = new DisplayTreeChangeEvent(children[index], false);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        delete children[index];
        children.erase(children.begin() + index);
    }
}

void DisplayObject::removeThis() {
    if (this->parent != NULL) {
        this->parent->removeImmediateChild(this);
    }
}

int DisplayObject::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObject::getChild(int index) {
    if (index < 0 || index > numChildren()) {
        return NULL;
    } else {
        return children[index];
    }
}

DisplayObject* DisplayObject::getChild(std::string id) {
    for (auto* child : children) {
        if (child->id == id) {
            return child;
        }
    }
    return nullptr;
}

void DisplayObject::update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) {
    for (auto* child : children) {
        child->update(pressedKeys, joystickState, pressedButtons);
    }
	// if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
	// 	position.x -= parallaxSpeed;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
	// 	position.x += parallaxSpeed;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
	// 	position.y -= parallaxSpeed;
	// }
	// if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
	// 	position.y += parallaxSpeed;
	// }
}

void DisplayObject::draw(AffineTransform& at) {
    applyTransformations(at);

    if (curTexture != NULL && visible) {
        SDL_Point origin = at.transformPoint(0, 0);
        SDL_Point upperRight = at.transformPoint(width, 0);
        SDL_Point lowerRight = at.transformPoint(width, height);
        SDL_Point corner = {0, 0};

        // std::cout << position.x << endl;
        int w = (int)distance(origin, upperRight);
        int h = (int)distance(upperRight, lowerRight);

        SDL_Rect dstrect = {origin.x, origin.y, w, h};

        SDL_RendererFlip flip;
        if (facingRight) {
            flip = SDL_FLIP_NONE;
        } else {
            flip = SDL_FLIP_HORIZONTAL;
        }

        SDL_SetTextureAlphaMod(curTexture, alpha);
        SDL_RenderCopyEx(renderer, curTexture, sourceRect, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
    }

    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (auto* child : children) {
        child->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);

    reverseTransformations(at);
}

void DisplayObject::applyTransformations(AffineTransform& at) {
    at.translate(position.x, position.y);
    at.rotate(rotation);
    at.scale(scaleX, scaleY);
    at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform& at) {
    at.translate(pivot.x, pivot.y);
    at.scale(1.0 / scaleX, 1.0 / scaleY);
    at.rotate(-rotation);
    at.translate(-position.x, -position.y);
}

void DisplayObject::updateSourceRect(SDL_Rect* s)
{
    if (!sourceRect){
        sourceRect = new SDL_Rect();
    }
    sourceRect->x = s->x;
    sourceRect->y = s->y;
    sourceRect->h = s->h;
    sourceRect->w = s->w;
}

int DisplayObject::getWidth() {
    return this->image->w;
}

int DisplayObject::getHeight() {
    return this->image->h;
}

void DisplayObject::getGlobalTransform(AffineTransform& at)
{
	//if DO has parent
	if(parent != NULL)
	{
		parent->getGlobalTransform(at);
        if (parent->type != "Camera"){
            at.translate(parent->pivot.x, parent->pivot.y);
        }
	}
	
	//at = parent's global
	//undo parent's pivot
	//apply this object's transform to at
	this->applyTransformations(at);
}

// Override this method to handle collisions by yourself
// instead of relying on CollisionSystem's default collision resolution
// (which is just to move the objects so they're not colliding)
bool DisplayObject::onCollision(DisplayObject* other) {
    return false;
}

Hitbox DisplayObject::getHitbox() {
    AffineTransform at;
	this->getGlobalTransform(at);
	return {
        at.transformPoint(0, 0),
        at.transformPoint(width, 0),
        at.transformPoint(0, height),
        at.transformPoint(width, height),
    };
}

void DisplayObject::drawHitbox(SDL_Color color) {
    Hitbox hitbox = this->getHitbox();

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    auto [r, g, b, a] = color;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, hitbox.ul.x, hitbox.ul.y, hitbox.ur.x, hitbox.ur.y);
    SDL_RenderDrawLine(renderer, hitbox.ul.x, hitbox.ul.y, hitbox.ll.x, hitbox.ll.y);
    SDL_RenderDrawLine(renderer, hitbox.ll.x, hitbox.ll.y, hitbox.lr.x, hitbox.lr.y);
    SDL_RenderDrawLine(renderer, hitbox.ur.x, hitbox.ur.y, hitbox.lr.x, hitbox.lr.y);
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
}

double DisplayObject::distance(SDL_Point& p1, SDL_Point& p2) {
    return std::sqrt(((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.x - p1.x) * (p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point& origin, SDL_Point& p) {
    int y = p.y - origin.y;
    int x = p.x - origin.x;
    return std::atan2(y, x) * 180 / PI;
}

void DisplayObject::setSurface(SDL_Surface* s) {
    if (this->image){
        SDL_FreeSurface(this->image);
    }
    this->image = s;
}

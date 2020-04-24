#include "DisplayObject.h"

#include "Game.h"
#include "events/DisplayTreeChangeEvent.h"
#include "events/NewSceneEvent.h"
#include "events/TweenEvent.h"
#include "tweens/TweenJuggler.h"
#include "things/Player.h"

#include <algorithm>
#include <cmath>
#include <iostream>

DisplayObject::DisplayObject(const std::string& id) {
    this->id = id;
    this->saveType = this->type;

    this->renderer = Game::renderer;

    this->image = nullptr;
    this->texture = nullptr;
    this->curTexture = nullptr;

    this->hitbox = {{0, 0}, {width, 0}, {0, height}, {width, height}};
}

DisplayObject::DisplayObject(const std::string& id, const std::string& path)
    : DisplayObject(id) {
    this->imgPath = path;

    loadTexture(path, Game::renderer);
    this->hitbox = {{0, 0}, {width, 0}, {0, height}, {width, height}};
}

DisplayObject::DisplayObject(const std::string& id, const std::string& path, SDL_Renderer* r)
    : DisplayObject(id) {
    this->imgPath = path;
    this->renderer = r;

    loadTexture(path, r);
    this->hitbox = {{0, 0}, {width, 0}, {0, height}, {width, height}};
}

DisplayObject::DisplayObject(const std::string& id, int red, int green, int blue)
    : DisplayObject(id, red, green, blue, 100, 100) {
}

DisplayObject::DisplayObject(const std::string& id, int red, int green, int blue, int width, int height)
    : DisplayObject(id, red, green, blue, width, height, Game::renderer) {
}

DisplayObject::DisplayObject(const std::string& id, int red, int green, int blue, int width, int height, SDL_Renderer* r)
    : DisplayObject(id) {
    this->id = id;

    this->red = red;
    this->blue = blue;
    this->green = green;

    this->width = width;
    this->height = height;

    this->renderer = r;

    this->loadRGBTexture(red, green, blue, width, height, r);
    this->hitbox = {{0, 0}, {width, 0}, {0, height}, {width, height}};
}

// TODO: Needs to copy children
DisplayObject::DisplayObject(const DisplayObject& other) {
    this->renderer = other.renderer;
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
    this->saveType = other.saveType;
    this->loadTexture(this->imgPath, Game::renderer);
    this->hitbox = {{0, 0}, {width, 0}, {0, height}, {width, height}};
}

DisplayObject::~DisplayObject() {
    if (image != nullptr) {
        SDL_FreeSurface(image);
    }

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void DisplayObject::loadTexture(const std::string& filepath, SDL_Renderer* r) {
    image = IMG_Load(filepath.c_str());
    texture = SDL_CreateTextureFromSurface(r, image);
    setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue, int width, int height, SDL_Renderer* r) {
    image = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0x000000ff);
    SDL_FillRect(image, nullptr, SDL_MapRGB(image->format, red, green, blue));
    texture = SDL_CreateTextureFromSurface(r, image);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    setTexture(texture);
}

// TODO: Can this just pull from getGlobalTransform
SDL_Point DisplayObject::getGlobalPosition() const {
    DisplayObject* parent = this->parent;
    std::vector<DisplayObject*> parentList;
    while (parent != nullptr) {
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

void DisplayObject::addChild(std::shared_ptr<DisplayObject> child) {
    if (child->parent != this) {
        children.push_back(child);
        child->parent = this; // make sure to include reverse reference also

        auto* event = new DisplayTreeChangeEvent(child, true);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;
    }
}

void DisplayObject::removeImmediateChild(std::shared_ptr<DisplayObject> child) {
    auto it = std::find(this->children.cbegin(), this->children.cend(), child);
    if (it != this->children.cend()) {
        auto* event = new DisplayTreeChangeEvent(*it, false);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        // delete *it;
        objectsToErase.push_back(*it);
    }
}

void DisplayObject::removeImmediateChild(std::string id) {
    auto it = std::find_if(this->children.cbegin(), this->children.cend(), [&](const auto child) { return child->id == id; });
    if (it != this->children.cend()) {
        auto* event = new DisplayTreeChangeEvent(*it, true);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        objectsToErase.push_back(*it);
    }
}

void DisplayObject::removeChild(size_t index) {
    if (index < children.size()) {
        auto* event = new DisplayTreeChangeEvent(children[index], false);
        EventDispatcher::getInstance().dispatchEvent(event);
        delete event;

        children.erase(children.begin() + index);
    }
}

void DisplayObject::removeThis() {
    if (this->parent != nullptr) {
        this->parent->removeImmediateChild(this->id);
    }
}

int DisplayObject::numChildren() const {
    return this->children.size();
}

std::shared_ptr<DisplayObject> DisplayObject::getChild(int index) const {
    if (index < 0 || index > numChildren()) {
        return nullptr;
    } else {
        return children[index];
    }
}

std::shared_ptr<DisplayObject> DisplayObject::getChild(const std::string& id) const {
    for (auto child : children) {
        if (child->id == id) {
            return child;
        }
    }
    return nullptr;
}

void DisplayObject::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    for (auto child : children) {
        child->update(pressedKeys, joystickState, pressedButtons);
    }

    // Clear ourselves of any deleted children
    for (auto object : objectsToErase) {
        children.erase(std::remove(children.begin(), children.end(), object), children.cend());
    }
    objectsToErase.clear();
}

void DisplayObject::draw(AffineTransform& at) {
    applyTransformations(at);

    if (curTexture != nullptr && visible) {
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
    for (auto child : children) {
        child->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);

    reverseTransformations(at);
}

void DisplayObject::applyTransformations(AffineTransform& at) const {
    at.translate(position.x, position.y);
    at.rotate(rotation);
    at.scale(scaleX, scaleY);
    at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform& at) const {
    at.translate(pivot.x, pivot.y);
    at.scale(1.0 / scaleX, 1.0 / scaleY);
    at.rotate(-rotation);
    at.translate(-position.x, -position.y);
}

void DisplayObject::updateSourceRect(SDL_Rect* s)
{
    if (sourceRect == nullptr) {
        sourceRect = new SDL_Rect();
    }
    sourceRect->x = s->x;
    sourceRect->y = s->y;
    sourceRect->h = s->h;
    sourceRect->w = s->w;
}

void DisplayObject::scaleHeight(int h){
    double ratio = (double) h / (double) height;
    this->scaleX = ratio;
    this->scaleY = ratio;
}

void DisplayObject::scaleWidth(int w){

}

void DisplayObject::getGlobalTransform(AffineTransform& at) const {
	//if DO has parent
	if(parent != nullptr)
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
bool DisplayObject::onCollision(std::shared_ptr<DisplayObject> other /*other*/) {
    return false;
}

Hitcircle DisplayObject::getHitcircle() const {
    AffineTransform at;
    this->getGlobalTransform(at);
    SDL_Point center = at.transformPoint(this->width / 2, this->height / 2);
    SDL_Point edge = at.transformPoint(0, this->height / 2);
    double radius = distance(center, edge);
    return {
        center,
        radius,
    };
}

void DisplayObject::drawHitcircle(SDL_Color color) const {
    Hitcircle hitcircle = this->getHitcircle();

    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(renderer, &oldR, &oldG, &oldB, &oldA);

    auto [r, g, b, a] = color;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // https://stackoverflow.com/a/48291620/5661593
    const int32_t diameter = hitcircle.radius * 2;

    int32_t x = hitcircle.radius - 1;
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = tx - diameter;

    while (x >= y) {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, hitcircle.center.x + x, hitcircle.center.y - y);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x + x, hitcircle.center.y + y);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x - x, hitcircle.center.y - y);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x - x, hitcircle.center.y + y);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x + y, hitcircle.center.y - x);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x + y, hitcircle.center.y + x);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x - y, hitcircle.center.y - x);
        SDL_RenderDrawPoint(renderer, hitcircle.center.x - y, hitcircle.center.y + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += tx - diameter;
        }
    }
    SDL_SetRenderDrawColor(renderer, oldR, oldG, oldB, oldA);
}

Hitbox DisplayObject::getHitbox() const {
    AffineTransform at;
	this->getGlobalTransform(at);
	return {
        // at.transformPoint(hitbox.ul.x, hitbox.ul.y),
        // at.transformPoint(hitbox.ur.x, hitbox.ur.y),
        // at.transformPoint(hitbox.ll.x, hitbox.ll.y),
        // at.transformPoint(hitbox.lr.x, hitbox.lr.y),
        at.transformPoint(0, 0),
        at.transformPoint(width, 0),
        at.transformPoint(0, height),
        at.transformPoint(width, height),
    };
}

void DisplayObject::drawHitbox(SDL_Color color) const {
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
    if (this->image != nullptr) {
        SDL_FreeSurface(this->image);
    }
    this->image = s;
}

void DisplayObject::propogateEvent(Event* e, std::shared_ptr<DisplayObject> root) {

    if (e->getType() == NewSceneEvent::FADE_OUT_EVENT){
        EventDispatcher::getInstance().removeEventListener(root.get(), NewSceneEvent::FADE_OUT_EVENT);
        for (auto child : root->children) {
            propogateEvent(e, child);
        }
        auto out_transition = std::make_shared<Tween>("out_transition", root);
		out_transition->animate(TweenableParams::ALPHA, 255, 0, 200, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(out_transition);
    }

    if (e->getType() == NewSceneEvent::FADE_IN_EVENT){
        EventDispatcher::getInstance().removeEventListener(root.get(), NewSceneEvent::FADE_IN_EVENT);
        for (auto child : root->children) {
            propogateEvent(e, child);
        }
        auto in_transition = std::make_shared<Tween>("in_transition", root);
		in_transition->animate(TweenableParams::ALPHA, 0, 255, 200, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(in_transition);
	}

}

void DisplayObject::handleEvent(Event* e){
    // once tween is done, delete scene
    if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT) {
        if (((TweenEvent*) e)->getTween()->getID() == "out_transition") {
            if (this->type == "Scene") {
                EventDispatcher::getInstance().removeEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
                for (auto child : children) {
                    this->removeImmediateChild(child);
                }

                this->removeThis();
            }
        }
    }
    // scale out event
    if (e->getType() == NewSceneEvent::SCALE_OUT_EVENT) {
        EventDispatcher::getInstance().removeEventListener(this, NewSceneEvent::SCALE_OUT_EVENT);
        double curScaleX = this->scaleX;
        double curScaleY = this->scaleY;
        auto out_transition = std::make_shared<Tween>("out_transition", shared_from_this());
		out_transition->animate(TweenableParams::SCALE_X, curScaleX, 0, 200, TweenParam::EASE_IN);
		out_transition->animate(TweenableParams::SCALE_Y, curScaleY, 0, 200, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(out_transition);
    }
    // scale in event
    if (e->getType() == NewSceneEvent::SCALE_IN_EVENT) {
        EventDispatcher::getInstance().removeEventListener(this, NewSceneEvent::SCALE_IN_EVENT);
        auto in_transition = std::make_shared<Tween>("in_transition", shared_from_this());
		in_transition->animate(TweenableParams::SCALE_X, 0, 1, 200, TweenParam::EASE_IN);
		in_transition->animate(TweenableParams::SCALE_Y, 0, 1, 200, TweenParam::EASE_IN);
		TweenJuggler::getInstance().add(in_transition);
    }
    // scale in event
    if (e->getType() == NewSceneEvent::FADE_IN_EVENT || e->getType() == NewSceneEvent::FADE_OUT_EVENT) {
        propogateEvent(e, shared_from_this());
    }

}


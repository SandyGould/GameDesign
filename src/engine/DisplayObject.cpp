#include "DisplayObject.h"
#include "Game.h"
#include "events/ClickEvent.h"
#include "events/DragEvent.h"

#include <algorithm>
#include <cmath>
#include <iostream>

constexpr auto PI = 3.14159265;

DisplayObject::DisplayObject() {
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(std::string id, std::string filepath) {
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);
}

DisplayObject::DisplayObject(std::string id, int red, int green, int blue) {
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject() {
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
}

void DisplayObject::loadTexture(std::string filepath) {
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue) {
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t) {
	this->curTexture = t;
}

void DisplayObject::update(std::unordered_set<SDL_Scancode> pressedKeys) {

}

void DisplayObject::draw(AffineTransform& at) {
	applyTransformations(at);

	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		// std::cout << position.x << endl;
		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		this->dstrect = { origin.x, origin.y, w, h };

		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}

		SDL_SetTextureAlphaMod(curTexture, alpha);
		SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
	}

	reverseTransformations(at);
}

void DisplayObject::handleEvent(Event* e) {
	if (e->getType() == ClickEvent::CLICK_EVENT) {
		ClickEvent* event = static_cast<ClickEvent*>(e);
		if (this->dstrect.x <= event->x && event->x <= this->dstrect.x + this->dstrect.w &&
			this->dstrect.y <= event->y && event->y <= this->dstrect.y + this->dstrect.h) {
			std::cout << this->id << " handling a mouse event at (" << event->x << ", " << event->y << ")" << std::endl;
		}
	} else if (e->getType() == DragEvent::DRAG_EVENT) {
		DragEvent* event = static_cast<DragEvent*>(e);
		if (this->dstrect.x <= event->x && event->x <= this->dstrect.x + this->dstrect.w &&
			this->dstrect.y <= event->y && event->y <= this->dstrect.y + this->dstrect.h) {
			// todo
		}
	}
}

void DisplayObject::applyTransformations(AffineTransform& at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
	at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform& at) {
	at.translate(pivot.x, pivot.y);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

int DisplayObject::getWidth() {
	return this->image->w;
}

int DisplayObject::getHeight() {
	return this->image->h;
}

double DisplayObject::distance(SDL_Point& p1, SDL_Point& p2) {
	return std::sqrt(((p2.y - p1.y) * (p2.y - p1.y)) + ((p2.x - p1.x) * (p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point& origin, SDL_Point& p) {
	int y = p.y - origin.y;
	int x = p.x - origin.x;
	return std::atan2(y, x) * 180 / PI;
}

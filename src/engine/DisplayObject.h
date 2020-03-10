#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include "AffineTransform.h"
#include "events/EventDispatcher.h"
#include "events/EventListener.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <set>
#include <string>
#include <vector>

class DisplayObject {

public:
	std::string id = "DEFAULT_ID";
	std::string imgPath = "";
	std::string type = "DisplayObject";

	DisplayObject* parent = NULL;

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 255;
	SDL_Rect sourceRect = {0,0,416,454};

	bool isRGB = false;

	DisplayObject();
	DisplayObject(std::string id, std::string path);
	DisplayObject(std::string id, int red, int green, int blue);
	virtual ~DisplayObject();
	
	virtual void update(std::set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform& at);

	void loadTexture(std::string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);

	void applyTransformations(AffineTransform& at);
	void reverseTransformations(AffineTransform& at);

	int getWidth();
	int getHeight();

	bool visible = true;
	SDL_Point position = {0, 0};
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	bool facingRight = true;

	bool hasCollision = false;

private:
	double distance(SDL_Point& p1, SDL_Point& p2);
	double calculateRotation(SDL_Point& origin, SDL_Point& p);
	
	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

#endif
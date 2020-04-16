#pragma once

#include "AffineTransform.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <unordered_set>
#include <string>
#include <vector>

static constexpr auto PI = 3.14159265;

struct jState {
	Sint16 xVal1;
	Sint16 yVal1;
	Sint16 xVal2;
	Sint16 yVal2;
};

struct Hitbox {
    SDL_Point ul;
    SDL_Point ur;
    SDL_Point ll;
    SDL_Point lr;
};

class DisplayObject {

public:
	std::string id = "DEFAULT_ID";
	std::string imgPath = "";
	std::string type = "DisplayObject";

	DisplayObject* parent = NULL;
	std::string parentId = "";

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 255;
	SDL_Rect* sourceRect = NULL;

	bool isRGB = false;

    explicit DisplayObject(std::string id);
    DisplayObject(std::string id, std::string path);
	DisplayObject(std::string id, std::string path, SDL_Renderer* r);
	DisplayObject(std::string id, int red, int green, int blue);
	DisplayObject(std::string id, int red, int green, int blue, int width, int height);
	DisplayObject(std::string id, int red, int green, int blue, int width, int height, SDL_Renderer* r);
	DisplayObject(const DisplayObject& other);
	virtual ~DisplayObject();

    void loadTexture(std::string filepath, SDL_Renderer* r);
    void loadRGBTexture(int red, int green, int blue, int width, int height, SDL_Renderer* r);
    void setTexture(SDL_Texture* t);
	void setSurface(SDL_Surface* s);

    void addChild(DisplayObject* child);
    void removeImmediateChild(DisplayObject* child);
    void removeImmediateChild(std::string id);
    void removeChild(size_t index);
    void removeThis();

    int numChildren();
    DisplayObject* getChild(int index);
    DisplayObject* getChild(std::string id);

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	virtual void draw(AffineTransform& at);

	void applyTransformations(AffineTransform& at);
	void reverseTransformations(AffineTransform& at);

	SDL_Point getGlobalPosition();
	void updateSourceRect(SDL_Rect* s);

	int getWidth();
	int getHeight();

	void getGlobalTransform(AffineTransform& at);

    virtual bool onCollision(DisplayObject* other);
	
	Hitbox getHitbox();
    void drawHitbox();

    bool visible = true;
    SDL_Point position = {0, 0};

	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	bool facingRight = true;

	SDL_Renderer* renderer;

	bool hasCollision = false;

	// FIXME: Probably a very dirty hack please find a better way to grab global coords
	SDL_Rect dstrect;
	double parallaxSpeed = 0.0;

    std::vector<DisplayObject*> children;

private:
	double distance(SDL_Point& p1, SDL_Point& p2);
	double calculateRotation(SDL_Point& origin, SDL_Point& p);

	SDL_Texture* texture = NULL;
	SDL_Surface* image = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;
};

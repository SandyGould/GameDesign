#pragma once

#include "AffineTransform.h"
#include "events/Event.h"
#include "events/EventListener.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

enum class CollisionDirection;

static constexpr auto PI = 3.14159265;

struct jState {
	Sint16 xVal1;
	Sint16 yVal1;
	Sint16 xVal2;
	Sint16 yVal2;
};

enum class HitboxType {
    Rectangle,
    Circle,
};

struct Hitcircle {
    SDL_Point center;
    double radius;
};

struct Hitbox {
    SDL_Point ul;
    SDL_Point ur;
    SDL_Point ll;
    SDL_Point lr;
};

class DisplayObject : public EventListener, public std::enable_shared_from_this<DisplayObject> {

public:
	std::string id = "DEFAULT_ID";
	std::string imgPath = "";
	std::string type = "DisplayObject";
	std::string saveType;

    // Purposely not a weak_ptr!
    // We do not control the parent, and we need references to it in the constructor
	DisplayObject* parent = nullptr;

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 255;
	SDL_Rect* sourceRect = nullptr;

    explicit DisplayObject(const std::string& id);
    DisplayObject(const std::string& id, const std::string& path);
	DisplayObject(const std::string& id, const std::string& path, SDL_Renderer* r);
	DisplayObject(const std::string& id, int red, int green, int blue);
	DisplayObject(const std::string& id, int red, int green, int blue, int width, int height);
	DisplayObject(const std::string& id, int red, int green, int blue, int width, int height, SDL_Renderer* r);
	DisplayObject(const DisplayObject& other);
	virtual ~DisplayObject();

    void loadTexture(const std::string& filepath);
    void loadRGBTexture(int red, int green, int blue, int width, int height);
    void setTexture(SDL_Texture* t);
	void setSurface(SDL_Surface* s);
	virtual void setRenderer(SDL_Renderer* r);

    void addChild(const std::shared_ptr<DisplayObject>& child);
    void removeImmediateChild(const std::shared_ptr<DisplayObject>& child);
    void removeImmediateChild(std::string id);
    void removeChild(size_t index);
    void removeThis();

    [[nodiscard]] int numChildren() const;
    [[nodiscard]] std::shared_ptr<DisplayObject> getChild(int index) const;
    [[nodiscard]] std::shared_ptr<DisplayObject> getChild(const std::string& id) const;

	virtual void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons);
	virtual void draw(AffineTransform& at);

	void applyTransformations(AffineTransform& at) const;

	void updateSourceRect(SDL_Rect* s);

	void scaleHeight(int h);
	void scaleWidth(int w);

	void getGlobalTransform(AffineTransform& at) const;
    [[nodiscard]] SDL_Point getGlobalPosition() const;

    virtual bool onCollision(std::shared_ptr<DisplayObject> other, CollisionDirection direction1, CollisionDirection direction2);

    [[nodiscard]] Hitcircle getHitcircle() const;
    void drawHitcircle(SDL_Color color = {255, 0, 0, SDL_ALPHA_OPAQUE}) const;

	void setHitbox(double left, double right, double top, double bottom);
	void setHitbox(int left, int right, int top, int bottom);
    [[nodiscard]] Hitbox getHitbox() const;
    void drawHitbox(SDL_Color color = {255, 0, 0, SDL_ALPHA_OPAQUE}) const;

	double hitbox_leftEdge   = 0.0;
	double hitbox_rightEdge  = 1.0;
	double hitbox_topEdge    = 0.0;
	double hitbox_bottomEdge = 1.0;

	void propogateEvent(Event* e, const std::shared_ptr<DisplayObject>& root);
	void handleEvent(Event* e) override;

    bool visible = true;
    SDL_Point position = {0, 0};
    // SDL_Point orig_position = {0, 0}; // Used for parallaxing (in Layer.cpp)

	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	bool facingRight = true;
    HitboxType hitboxType = HitboxType::Rectangle;
	SDL_Renderer* renderer;

	bool hasCollision = false;

	double parallaxSpeed = 1.0;

    std::vector<std::shared_ptr<DisplayObject>> children;

	// for debugging
	void printDisplayTreeHelper(const std::shared_ptr<DisplayObject>& root, const std::string& indentation);
	void printDisplayTree();

private:
	static double distance(SDL_Point& p1, SDL_Point& p2);
	static double calculateRotation(SDL_Point& origin, SDL_Point& p);

	SDL_Texture* texture = nullptr;
	SDL_Surface* image = nullptr;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture = nullptr;

    // Keep track of any objects that were erased during our update loop,
    // so that we can properly erase them from children afterwards
    std::vector<std::shared_ptr<DisplayObject>> objectsToAdd;
    std::queue<std::shared_ptr<DisplayObject>> objectsToErase;
};

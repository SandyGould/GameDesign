#pragma once

#include "DisplayObject.h"
#include "Sprite.h"
#include "events/Event.h"
#include "events/EventListener.h"

using namespace std;

enum class Orientation {
    Colinear,
    Clockwise,
    CounterClockwise,
};

class CollisionSystem : public EventListener {

public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    //checks collisions between pairs of DOs where the corresponding types have been requested
    //to be checked (via a single call to watchForCollisions) below.
    void update();

    //This system watches the game's display tree and is notified whenever a display object is placed onto
    //or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
    void handleEvent(Event* e) override;

    //This function asks the collision system to start checking for collisions between all pairs
    //of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
    //against all platform objects that are in the current scene.
    void watchForCollisions(const string& type1, const string& type2);
    void pairObjectWithType(DisplayObject* object, const string& type);

    //returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
    //	SDL_Point* DisplayObject::getGlobalHitbox();
    static bool collidesWith(DisplayObject* obj1, DisplayObject* obj2);

    //Resolves the collision that occurred between d and other
    //xDelta1 and yDelta1 are the amount d moved before causing the collision.
    //xDelta2 and yDelta2 are the amount other moved before causing the collision.
    void resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2);

    static bool cornerIn(SDL_Point p1, SDL_Point q1, SDL_Point q2, SDL_Point q3, SDL_Point q4);
    static bool checklinesegments(SDL_Point p1, SDL_Point p2, SDL_Point q1, SDL_Point q2);
    static Orientation getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3);
    static bool onSegment(SDL_Point p1, SDL_Point p2, SDL_Point p3);

private:
    // platform -> [platform1, platform2, platform3, ...]
    unordered_map<string, unordered_set<DisplayObject*>> displayObjectsMap;

    // {[player, platform1], [player, platform2], ...}
    vector<pair<DisplayObject*, DisplayObject*>> collisionPairs;

    // player -> [player, platform, ...]
    unordered_map<string, unordered_set<string>> collisionTypes;
};

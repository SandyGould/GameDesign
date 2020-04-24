#pragma once

#include "DisplayObject.h"
#include "events/EventListener.h"

#include <queue>

using namespace std;

enum class Orientation {
    Colinear,
    Clockwise,
    CounterClockwise,
};

class CollisionSystem : public EventListener {

public:
    CollisionSystem();
    ~CollisionSystem();

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

    // Is a point inside of a hitbox?
    static bool isInside(SDL_Point point, Hitbox hitbox);

private:
    void buildDisplayMap(shared_ptr<DisplayObject> object);

    void pairObjectWithType(shared_ptr<DisplayObject> object, const string& type);

    void addObjects(const shared_ptr<DisplayObject>& object);
    void eraseObjects(const shared_ptr<DisplayObject>& object);

    // Returns true iff obj1 hitbox and obj2 hitbox overlap
    static bool collidesWith(shared_ptr<DisplayObject> obj1, shared_ptr<DisplayObject> obj2);

    // Resolves the collision that occurred between d and other
    // xDelta1 and yDelta1 are the amount d moved before causing the collision.
    // xDelta2 and yDelta2 are the amount other moved before causing the collision.
    static void resolveCollision(shared_ptr<DisplayObject> d, shared_ptr<DisplayObject> other, int xDelta1, int yDelta1, int xDelta2, int yDelta2);

    static bool isIntersecting(SDL_Point p1, SDL_Point p2, SDL_Point q1, SDL_Point q2);
    static bool isIntersecting(Hitcircle hitcircle, pair<SDL_Point, SDL_Point> line);
    static Orientation getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3);

    // platform -> [platform1, platform2, platform3, ...]
    unordered_map<string, unordered_set<std::shared_ptr<DisplayObject>>> displayObjectsMap;

    // {[player, platform1], [player, platform2], ...}
    vector<pair<std::shared_ptr<DisplayObject>, std::shared_ptr<DisplayObject>>> collisionPairs;

    // player -> [player, platform, ...]
    unordered_map<string, unordered_set<string>> collisionTypes;

    // *Must* be local coordinates!
    // i.e. obj->position, NOT obj->getHitbox().ul
    unordered_map<std::shared_ptr<DisplayObject>, SDL_Point> prevPositions;

    // Keep track of any objects that were added/erased during our update loop,
    // so that we can properly add/erase them to/from collisionPairs afterwards
    queue<pair<std::shared_ptr<DisplayObject>, std::shared_ptr<DisplayObject>>> pairsToAdd;
    vector<std::shared_ptr<DisplayObject>> objectsToErase;
};

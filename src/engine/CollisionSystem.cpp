#include "CollisionSystem.h"

#include "Game.h"
#include "events/DisplayTreeChangeEvent.h"

#include <algorithm>
#include <iostream>

CollisionSystem::CollisionSystem() {
    // Set up the listener to build out the display map
    EventDispatcher::getInstance().addEventListener(this, DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT);

    // Keep track of any objects that were added before we were created
    this->buildDisplayMap(Game::instance->container);
}

void CollisionSystem::buildDisplayMap(shared_ptr<DisplayObject> object) {
    auto it = displayObjectsMap.find(object->type);
    if (it != displayObjectsMap.cend()) {
        it->second.insert(object);
    } else {
        displayObjectsMap.try_emplace(object->type, unordered_set<shared_ptr<DisplayObject>>({object}));
    }

    for (auto child : object->children) {
        this->buildDisplayMap(child);
    }
}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
    for (auto& [object1, object2] : collisionPairs) {
        // Before we do anything! We must make sure we're not trying to
        // operate on objects that have already been removed
        // (We cannot delete them from collisionPairs immediately b/c
        // that would invalidate the iterator we're looping on)
        if (find(objectsToErase.cbegin(), objectsToErase.cend(), object1) != objectsToErase.cend() ||
            find(objectsToErase.cbegin(), objectsToErase.cend(), object2) != objectsToErase.cend()) {
            break;
        }

        SDL_Point obj1Position = object1->position;
        SDL_Point obj2Position = object2->position;

        SDL_Point obj1Prev = prevPositions.at(object1);
        SDL_Point obj2Prev = prevPositions.at(object2);

        if (obj1Prev.x == obj1Position.x && obj1Prev.y == obj1Position.y &&
            obj2Prev.x == obj2Position.x && obj2Prev.y == obj2Position.y) {
            // Wait, they didn't move! They couldn't have collided, then.
            continue;
        }

        // More optimizations possible:
        // - Only check for collisions for visible objects
        // - Only check for collisions for objects in the camera view

        if (collidesWith(object1, object2)) {
            int xD1 = obj1Position.x - obj1Prev.x;
            int yD1 = obj1Position.y - obj1Prev.y;
            int xD2 = obj2Position.x - obj2Prev.x;
            int yD2 = obj2Position.y - obj2Prev.y;
            resolveCollision(object1, object2, xD1, yD1, xD2, yD2);
        }
    }

    // Add new pairs
    while (!pairsToAdd.empty()) {
        collisionPairs.emplace_back(pairsToAdd.front());
        pairsToAdd.pop();
    }

    // Clear ourselves of any deleted elements
    for (auto object : objectsToErase) {
        collisionPairs.erase(remove_if(collisionPairs.begin(),
                                       collisionPairs.end(),
                                       [&](auto x) {
                                           return x.first == object || x.second == object;
                                       }),
                             collisionPairs.cend());
    }
    objectsToErase.clear();

    // Update previous positions
    for (auto& [object, _] : prevPositions) {
        prevPositions.at(object) = object->position;
    }
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {
    if (e->getType() == DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT) {
        DisplayTreeChangeEvent* event = static_cast<DisplayTreeChangeEvent*>(e);
        shared_ptr<DisplayObject> object(event->object);
        const string type = object->type;
        if (event->added) {
            auto it = displayObjectsMap.find(type);
            if (it != displayObjectsMap.cend()) {
                it->second.emplace(object);
            } else {
                displayObjectsMap.try_emplace(type, unordered_set<shared_ptr<DisplayObject>>{object});
            }

            if (collisionTypes.find(type) != collisionTypes.cend()) {
                for (auto& otherType : collisionTypes.at(type)) {
                    if (displayObjectsMap.find(otherType) != displayObjectsMap.cend()) {
                        this->pairObjectWithType(object, otherType);
                    }
                }
            }
        } else {
            // Defer erasing from collisionPairs as it's possible that
            // we're in the middle of an update() loop, and deleting now
            // would invalidate the iterators
            objectsToErase.emplace_back(object);
            displayObjectsMap.at(type).erase(object);
            prevPositions.erase(object);
        }
    }
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(const string& type1, const string& type2) {
    if (displayObjectsMap.find(type1) != displayObjectsMap.cend() &&
        displayObjectsMap.find(type2) != displayObjectsMap.cend()) {
        for (auto& object : displayObjectsMap.at(type1)) {
            this->pairObjectWithType(object, type2);
        }
    }

    auto it = collisionTypes.find(type1);
    if (it != collisionTypes.cend()) {
        it->second.insert(type2);
    }

    it = collisionTypes.find(type2);
    if (it != collisionTypes.cend()) {
        it->second.insert(type1);
    }

    collisionTypes.try_emplace(type1, unordered_set<string>({type2}));
    collisionTypes.try_emplace(type2, unordered_set<string>({type1}));
}

void CollisionSystem::pairObjectWithType(shared_ptr<DisplayObject> object, const string& type) {
    for (auto& object2 : displayObjectsMap.at(type)) {
        // Here, we sort by type then ID to make sure the unordered_set
        // doesn't contain duplicates.
        if (object->type < type) {
            pairsToAdd.emplace(object, object2);
        } else if (object->type == type) {
            // Don't register for collision if the two objects are the same
            if (object->id < object2->id) {
                pairsToAdd.emplace(object, object2);
            } else if (object->id > object2->id) {
                pairsToAdd.emplace(object2, object);
            }
        } else {
            pairsToAdd.emplace(object2, object);
        }

        // Keep track of positions for collision deltas
        prevPositions.try_emplace(object, object->position);
        prevPositions.try_emplace(object2, object2->position);
    }
}

Orientation CollisionSystem::getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
    // Taken from https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // I have NO CLUE how this formula was derived, only that it has to do with slopes.
    int orientation = (p3.y - p1.y) * (p2.x - p3.x) - (p3.x - p1.x) * (p2.y - p3.y);
    if (orientation < 0) {
        return Orientation::CounterClockwise;
    } else if (orientation > 0) {
        return Orientation::Clockwise;
    } else {
        return Orientation::Colinear;
    }
}

// Loosely based off of https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool CollisionSystem::isIntersecting(SDL_Point p1, SDL_Point p2, SDL_Point q1, SDL_Point q2) {
    auto o1 = getOrientation(p1, p2, q1);
    auto o2 = getOrientation(p1, p2, q2);
    auto o3 = getOrientation(q1, q2, p1);
    auto o4 = getOrientation(q1, q2, p2);
    if (o1 != o2 && o3 != o4) {
        // Intersection
        return true;
    }

    // This is when the other object is touching us
    if (o1 == Orientation::Colinear && o2 == Orientation::Colinear &&
        o3 == Orientation::Colinear && o4 == Orientation::Colinear) {
        // min/max x and see if the other point is in between those two x's?
        if ((p1.x >= q1.x && p1.x <= q2.x || p1.x <= q1.x && p1.x >= q2.x ||
             p2.x >= q1.x && p2.x <= q2.x || p2.x <= q1.x && p2.x >= q2.x) &&
            (p1.y >= q1.y && p1.y <= q2.y || p1.y <= q1.y && p1.y >= q2.y ||
             p2.y >= q1.y && p2.y <= q2.y || p2.y <= q1.y && p2.y >= q2.y)) {
            return true;
        }
    }

    return false;
}

bool CollisionSystem::isIntersecting(Hitcircle hitcircle, pair<SDL_Point, SDL_Point> line) {
    // https://math.stackexchange.com/questions/275529/check-if-line-intersects-with-circles-perimeter
    double ax = line.first.x - hitcircle.center.x;
    double ay = line.first.y - hitcircle.center.y;
    double bx = line.second.x - hitcircle.center.x;
    double by = line.second.y - hitcircle.center.y;
    double a = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
    double b = 2 * (ax * (bx - ax) + ay * (by - ay));
    double c = ax * ax + ay * ay - hitcircle.radius * hitcircle.radius;
    double disc = b * b - 4 * a * c;
    if (disc <= 0) {
        return false;
    }

    double sqrtdisc = sqrt(disc);
    double t1 = (-b + sqrtdisc) / (2 * a);
    double t2 = (-b - sqrtdisc) / (2 * a);
    return (0 < t1 && t1 < 1) || (0 < t2 && t2 < 1);
}

bool CollisionSystem::isInside(SDL_Point point, Hitbox hitbox) {
    auto [ul, ur, ll, lr] = hitbox; // Wizardry! 🧙‍♂️

    // Important: due to floating-point rounding errors when scaling and rotating,
    // we are NOT guaranteed to be a rectangle, only a quadrilateral. Perform calculations accordingly.
    int area_quad_2x = abs(ul.x * (ur.y - ll.y) + ur.x * (ll.y - ul.y) + ll.x * (ul.y - ur.y)) +
                       abs(ll.x * (ur.y - lr.y) + ur.x * (lr.y - ll.y) + lr.x * (ll.y - ur.y));

    // Compute the area of each triangle that the point forms with the hitbox
    // https://www.mathopenref.com/coordtrianglearea.html
    // We ignore the divide by 2 so that we can keep these as ints, which makes comparison a lot simpler.
    int area_t1_2x = abs(point.x * (ul.y - ur.y) + ul.x * (ur.y - point.y) + ur.x * (point.y - ul.y));
    int area_t2_2x = abs(point.x * (ur.y - lr.y) + ur.x * (lr.y - point.y) + lr.x * (point.y - ur.y));
    int area_t3_2x = abs(point.x * (ll.y - lr.y) + ll.x * (lr.y - point.y) + lr.x * (point.y - ll.y));
    int area_t4_2x = abs(point.x * (ll.y - ul.y) + ll.x * (ul.y - point.y) + ul.x * (point.y - ll.y));

    return area_t1_2x + area_t2_2x + area_t3_2x + area_t4_2x == area_quad_2x;
}

// Returns true iff obj1 hitbox and obj2 hitbox overlap
bool CollisionSystem::collidesWith(shared_ptr<DisplayObject> obj1, shared_ptr<DisplayObject> obj2) {
    if (obj1->hitboxType == HitboxType::Rectangle && obj2->hitboxType == HitboxType::Rectangle) {
        Hitbox obj1Hitbox = obj1->getHitbox();
        Hitbox obj2Hitbox = obj2->getHitbox();

        // Do line segments intersect?
        if (isIntersecting(obj1Hitbox.ul, obj1Hitbox.ur, obj2Hitbox.ul, obj2Hitbox.ur) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ur, obj2Hitbox.ul, obj2Hitbox.ll) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ur, obj2Hitbox.ur, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ur, obj2Hitbox.ll, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ll, obj2Hitbox.ul, obj2Hitbox.ur) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ll, obj2Hitbox.ul, obj2Hitbox.ll) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ll, obj2Hitbox.ur, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ul, obj1Hitbox.ll, obj2Hitbox.ll, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ur, obj1Hitbox.lr, obj2Hitbox.ul, obj2Hitbox.ur) ||
            isIntersecting(obj1Hitbox.ur, obj1Hitbox.lr, obj2Hitbox.ul, obj2Hitbox.ll) ||
            isIntersecting(obj1Hitbox.ur, obj1Hitbox.lr, obj2Hitbox.ur, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ur, obj1Hitbox.lr, obj2Hitbox.ll, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ll, obj1Hitbox.lr, obj2Hitbox.ul, obj2Hitbox.ur) ||
            isIntersecting(obj1Hitbox.ll, obj1Hitbox.lr, obj2Hitbox.ul, obj2Hitbox.ll) ||
            isIntersecting(obj1Hitbox.ll, obj1Hitbox.lr, obj2Hitbox.ur, obj2Hitbox.lr) ||
            isIntersecting(obj1Hitbox.ll, obj1Hitbox.lr, obj2Hitbox.ll, obj2Hitbox.lr)) {
            return true;
        }

        // Is either object completely inside of each other?
        // We only need to check one point because we already checked intersections above
        return isInside(obj1Hitbox.ul, obj2Hitbox) || isInside(obj2Hitbox.ul, obj1Hitbox);
    } else if (obj1->hitboxType == HitboxType::Circle && obj2->hitboxType == HitboxType::Circle) {
        cout << "circle <-> circle collision detection not yet implemented" << endl;
        return false;
    } else {
        shared_ptr<DisplayObject> circle;
        shared_ptr<DisplayObject> rect;
        if (obj1->hitboxType == HitboxType::Circle) {
            circle = obj1;
            rect = obj2;
        } else {
            circle = obj2;
            rect = obj1;
        }

        Hitbox hitbox = rect->getHitbox();
        Hitcircle hitcircle = circle->getHitcircle();

        return isInside(hitcircle.center, hitbox) ||
               isIntersecting(hitcircle, {hitbox.ul, hitbox.ll}) ||
               isIntersecting(hitcircle, {hitbox.ul, hitbox.ur}) ||
               isIntersecting(hitcircle, {hitbox.ur, hitbox.lr}) ||
               isIntersecting(hitcircle, {hitbox.ll, hitbox.lr});
    }
}

// Resolves the collision that occurred between d and other
// xDelta1 and yDelta1 are the amount d moved before causing the collision.
// xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(shared_ptr<DisplayObject> d, shared_ptr<DisplayObject> other,
                                       int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
    // Give the objects the chance to handle the collision by themselves
    if (d->onCollision(other) || other->onCollision(d)) {
        return;
    }

    unsigned int maxD = max({abs(xDelta1), abs(yDelta1), abs(xDelta2), abs(yDelta2)});

    // Binary search collision resolution using the biggest delta
    for (int i = 0; i <= log2(maxD); i++) {
        // Halve deltas to find the midpoint, rounding away from 0
        xDelta1 = lround(xDelta1 / 2.0);
        yDelta1 = lround(yDelta1 / 2.0);
        xDelta2 = lround(xDelta2 / 2.0);
        yDelta2 = lround(yDelta2 / 2.0);

        // If we are colliding and we weren't colliding the last search,
        // move halfway back (using the deltas above).
        // Ditto if we aren't colliding, but were before.
        if (collidesWith(d, other)) {
            d->position.x -= xDelta1;
            d->position.y -= yDelta1;
            other->position.x -= xDelta2;
            other->position.y -= yDelta2;
        } else {
            d->position.x += xDelta1;
            d->position.y += yDelta1;
            other->position.x += xDelta2;
            other->position.y += yDelta2;
        }
    }

    // If we're still colliding after the binary search, fix that.
    if (collidesWith(d, other)) {
        d->position.x -= xDelta1;
        d->position.y -= yDelta1;
        other->position.x -= xDelta2;
        other->position.y -= yDelta2;
    }
}

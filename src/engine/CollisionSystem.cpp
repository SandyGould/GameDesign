#include "CollisionSystem.h"

#include "events/DisplayTreeChangeEvent.h"

#include <algorithm>
#include <iostream>

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
    for (auto& [object1, object2] : collisionPairs) {
        if (collidesWith(object1, object2)) {
            cout << object1->id << " and " << object2->id << " are colliding!" << endl;
            int xD1 = 0;
            int yD1 = 0;
            int xD2 = 0;
            int yD2 = 0;
            if (prevPositions.find(object1) != prevPositions.end() && prevPositions.find(object2) != prevPositions.end()){
                SDL_Point obj1Prev = prevPositions.at(object1);
                SDL_Point obj2Prev = prevPositions.at(object2);
                xD1 = object1->position.x - obj1Prev.x;
                yD1 = object1->position.y - obj1Prev.y;
                xD2 = object2->position.x - obj2Prev.x;
                yD2 = object2->position.y - obj2Prev.y;
            }
            this->resolveCollision(object1, object2, xD1, yD1, xD2, yD2);
        }
    }
    for (auto& objType : displayObjectsMap){
        for (auto& obj : displayObjectsMap.at(objType.first)){
            if (prevPositions.find(obj) == prevPositions.end()){
                prevPositions.emplace(obj, obj->position);
            }
            prevPositions.at(obj) = obj->position;
        }
    }
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {
    if (e->getType() == DisplayTreeChangeEvent::DISPLAY_TREE_CHANGE_EVENT) {
        DisplayTreeChangeEvent* event = static_cast<DisplayTreeChangeEvent*>(e);
        DisplayObject* object = event->object;
        const string type = object->type;
        if (event->added) {
            auto it = displayObjectsMap.find(type);
            if (it != displayObjectsMap.cend()) {
                it->second.insert(object);
            } else {
                displayObjectsMap.try_emplace(type, unordered_set<DisplayObject*>({object}));
            }

            if (collisionTypes.find(type) != collisionTypes.cend()) {
                for (auto& otherType : collisionTypes.at(type)) {
                    this->pairObjectWithType(object, otherType);
                }
            }
        } else {
            displayObjectsMap.at(event->object->type).erase(event->object);
            collisionPairs.erase(remove_if(collisionPairs.begin(),
                                           collisionPairs.end(),
                                           [&](auto x) {
                                               return x.first == object || x.second == object;
                                           }),
                                 collisionPairs.cend());
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

void CollisionSystem::pairObjectWithType(DisplayObject* object, const string& type) {
    for (auto& object2 : displayObjectsMap.at(type)) {
        // Here, we sort by type then ID to make sure the unordered_set
        // doesn't contain duplicates.
        if (object->type < type) {
            collisionPairs.emplace_back(object, object2);
        } else if (object->type == type) {
            // Don't register for collision if the two objects are the same
            if (object->id < object2->id) {
                collisionPairs.emplace_back(object, object2);
            } else if (object->id > object2->id) {
                collisionPairs.emplace_back(object2, object);
            }
        } else {
            collisionPairs.emplace_back(object2, object);
        }
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

bool CollisionSystem::onSegment(SDL_Point p1, SDL_Point p2, SDL_Point p3) {
    return min(p1.x, p3.x) <= p2.x && p2.x <= max(p1.x, p3.x) &&
           min(p1.y, p3.y) <= p2.y && p2.y <= max(p1.y, p3.y);
}

// Loosely based off of https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool CollisionSystem::checklinesegments(SDL_Point p1, SDL_Point p2, SDL_Point q1, SDL_Point q2) {
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

    if (o3 == Orientation::Colinear && onSegment(p2, p1, q2)) {
        return true;
    }

    if (o4 == Orientation::Colinear && onSegment(p2, q1, q2)) {
        return true;
    }

    return false;
}

bool CollisionSystem::cornerIn(SDL_Point foreign, SDL_Point ul, SDL_Point ur, SDL_Point ll, SDL_Point lr) {
    int area_rect = abs(ul.x * (ur.y - ll.y) + ur.x * (ll.y - ul.y) + ll.x * (ul.y - ur.y));

    // Compute the area of each triangle that the foreign point forms with the hitbox
    // https://www.mathopenref.com/coordtrianglearea.html
    // We ignore the divide by 2 so that we can keep these as ints, which makes comparison a lot simpler.
    int area_t1_2x = abs(foreign.x * (ul.y - ur.y) + ul.x * (ur.y - foreign.y) + ur.x * (foreign.y - ul.y));
    int area_t2_2x = abs(foreign.x * (ur.y - lr.y) + ur.x * (lr.y - foreign.y) + lr.x * (foreign.y - ur.y));
    int area_t3_2x = abs(foreign.x * (ll.y - lr.y) + ll.x * (lr.y - foreign.y) + lr.x * (foreign.y - ll.y));
    int area_t4_2x = abs(foreign.x * (ll.y - ul.y) + ll.x * (ul.y - foreign.y) + ul.x * (foreign.y - ll.y));

    return area_t1_2x + area_t2_2x + area_t3_2x + area_t4_2x == 2 * area_rect;
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
    obj1->getHitbox();
    obj2->getHitbox();
    //do line segments overlap?
    bool l_1 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ur, obj2->hitbox_ul, obj2->hitbox_ur);
    bool l_2 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ur, obj2->hitbox_ul, obj2->hitbox_ll);
    bool l_3 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ur, obj2->hitbox_ur, obj2->hitbox_lr);
    bool l_4 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ur, obj2->hitbox_ll, obj2->hitbox_lr);

    bool l_5 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ll, obj2->hitbox_ul, obj2->hitbox_ur);
    bool l_6 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ll, obj2->hitbox_ul, obj2->hitbox_ll);
    bool l_7 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ll, obj2->hitbox_ur, obj2->hitbox_lr);
    bool l_8 = checklinesegments(obj1->hitbox_ul, obj1->hitbox_ll, obj2->hitbox_ll, obj2->hitbox_lr);

    bool l_9 = checklinesegments(obj1->hitbox_ur, obj1->hitbox_lr, obj2->hitbox_ul, obj2->hitbox_ur);
    bool l_10 = checklinesegments(obj1->hitbox_ur, obj1->hitbox_lr, obj2->hitbox_ul, obj2->hitbox_ll);
    bool l_11 = checklinesegments(obj1->hitbox_ur, obj1->hitbox_lr, obj2->hitbox_ur, obj2->hitbox_lr);
    bool l_12 = checklinesegments(obj1->hitbox_ur, obj1->hitbox_lr, obj2->hitbox_ll, obj2->hitbox_lr);

    bool l_13 = checklinesegments(obj1->hitbox_ll, obj1->hitbox_lr, obj2->hitbox_ul, obj2->hitbox_ur);
    bool l_14 = checklinesegments(obj1->hitbox_ll, obj1->hitbox_lr, obj2->hitbox_ul, obj2->hitbox_ll);
    bool l_15 = checklinesegments(obj1->hitbox_ll, obj1->hitbox_lr, obj2->hitbox_ur, obj2->hitbox_lr);
    bool l_16 = checklinesegments(obj1->hitbox_ll, obj1->hitbox_lr, obj2->hitbox_ll, obj2->hitbox_lr);

    if (l_1 || l_2 || l_3 || l_4 || l_5 || l_6 || l_7 || l_8 || l_9 || l_10 || l_11 | l_12 || l_13 ||
        l_14 || l_15 || l_16) {
        return true;
    }

    // Is either object completely inside of each other?
    // We only need to check one point because we already checked intersections above
    const bool obj1InObj2 = cornerIn(obj1->hitbox_ul, obj2->hitbox_ul, obj2->hitbox_ur, obj2->hitbox_ll, obj2->hitbox_lr);
    const bool obj2InObj1 = cornerIn(obj2->hitbox_ul, obj1->hitbox_ul, obj1->hitbox_ur, obj1->hitbox_ll, obj1->hitbox_lr);

    return obj1InObj2 || obj2InObj1;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
    int maxD = max({abs(xDelta1), abs(yDelta1), abs(xDelta2), abs(yDelta2)});
    int m = 1;
    cout << maxD << endl;
    while (maxD >>= 1){
        ++m;
    }
    cout << m << endl;
    bool collideLast = false;
    for (int i = 0; i < m; ++i){
        if (xDelta1 >= 0){
            ++xDelta1;
        } else{
            --xDelta1;
        }
        if (yDelta1 >= 0){
            ++yDelta1;
        } else{
            --yDelta1;
        }
        if (xDelta2 >= 0){
            ++xDelta2;
        } else{
            --xDelta2;
        }
        if (yDelta2 >= 0){
            ++yDelta2;
        } else{
            --yDelta2;
        }
        
        xDelta1 /= 2;
        yDelta1 /= 2;
        xDelta2 /= 2;
        yDelta2 /= 2;
        if (collidesWith(d, other) && !collideLast){
            xDelta1 = -xDelta1;
            yDelta1 = -yDelta1;
            xDelta2 = -xDelta2;
            yDelta2 = -yDelta2;
            collideLast = true;
        } else if (!collidesWith(d, other) && collideLast){
            xDelta1 = -xDelta1;
            yDelta1 = -yDelta1;
            xDelta2 = -xDelta2;
            yDelta2 = -yDelta2;
            collideLast = false;
        }
        d->position.x += xDelta1;
        d->position.y += yDelta1;
        other->position.x += xDelta2;
        other->position.y += yDelta2;
    }
}

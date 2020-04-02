#include "CollisionSystem.h"

#include "events/DisplayTreeChangeEvent.h"

#include <algorithm>

CollisionSystem::CollisionSystem(){

}

//~CollisionSystem(){

//}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
    for (auto& [object1, object2] : collisionPairs) {
        if (this->collidesWith(object1, object2)) {
            // TODO: Deltas
            this->resolveCollision(object1, object2, 0, 0, 0, 0);
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
                    for (auto& otherObject : displayObjectsMap.at(otherType)) {
                        if (object->id != otherObject->id) {
                            if (type < otherType) {
                                collisionPairs.emplace_back(object, otherObject);
                            } else if (type == otherType) {
                                if (object->id < otherObject->id) {
                                    collisionPairs.emplace_back(object, otherObject);
                                } else {
                                    collisionPairs.emplace_back(otherObject, object);
                                }
                            } else {
                                collisionPairs.emplace_back(otherObject, object);
                            }
                        }
                    }
                }
            }
        } else {
            displayObjectsMap.at(event->object->type).erase(event->object);
            collisionPairs.erase(remove_if(collisionPairs.begin(), collisionPairs.end(), [&](auto x) { return x.first == object || x.second == object; }), collisionPairs.cend());
        }
    }
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(const string& type1, const string& type2) {
    if (displayObjectsMap.find(type1) != displayObjectsMap.cend()) {
        if (displayObjectsMap.find(type2) != displayObjectsMap.cend()) {
            for (auto& object : displayObjectsMap.at(type1)) {
                for (auto& object2 : displayObjectsMap.at(type2)) {
                    if (object->id != object2->id) {
                        if (type1 < type2) {
                            collisionPairs.emplace_back(object, object2);
                        } else if (type1 == type2) {
                            if (object->id < object2->id) {
                                collisionPairs.emplace_back(object, object2);
                            } else {
                                collisionPairs.emplace_back(object2, object);
                            }
                        } else {
                            collisionPairs.emplace_back(object2, object);
                        }
                    }
                }
            }
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

int CollisionSystem::getOrientation(SDL_Point p1, SDL_Point p2, SDL_Point p3)
{
    // 0 = collinear, 1 = clockwise, 2 = counterclockwise
    // double s1 = (p2.y - p1.y) / (p2.x - p1.x);
    // double s2 = (p3.y - p2.y) / (p3.x - p2.x);
    double s1 = atan2(p2.y - p1.y, p2.x - p1.x);
    double s2 = atan2(p3.y - p1.y, p3.x - p1.x);

    if (s1 < s2) {
        return 2;
    } else if (s1 > s2) {
        return 1;
    } else {
        return 0;
    }
}

bool CollisionSystem::checklinesegments(SDL_Point p1, SDL_Point p2, SDL_Point q1, SDL_Point q2)
{
    int o1 = getOrientation(p1, p2, q1);
    int o2 = getOrientation(p1, p2, q2);
    int o3 = getOrientation(q1, q2, p1);
    int o4 = getOrientation(q1, q2, p2);
    if(o1 != o2 && o3 != o4) {
        // Intersection
        return true;
    }

    // This is when the other object is touching us
    if (o1 == o2 == o3 == o4 == 0) {
        // min/max x and see if the other point is in between those two x's?
        if (p1.x <= q1.x && q1.x <= p2.x || p1.x <= q2.x && q2.x <= p2.x ||
            q1.x <= p1.x && p1.x <= q2.x || q1.x <= p2.x && p2.x <= q2.x) {
            return true;
        }
    }
    return false;
}

// Standard distance formula
double CollisionSystem::distance(SDL_Point& p1, SDL_Point& p2) {
    return std::sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
}

// will be entered in order foreign point, ul, ur, ll, lr
bool CollisionSystem::cornerIn(SDL_Point p1, SDL_Point q1, SDL_Point q2, SDL_Point q3, SDL_Point q4)
{
    // double area_rect = distance(q1,q2) * distance(q1,q3);
    int area_rect = abs(q1.x * (q2.y - q3.y) + q2.x * (q3.y - q1.y) + q3.x * (q1.y - q2.y));

    // Compute the area of each triangle that the foreign point forms with the hitbox
    // https://www.mathopenref.com/coordtrianglearea.html
    // We ignore the divide by 2 so that we can keep these as ints, which makes comparison a lot simpler.
    int area_t1_2x = abs(p1.x * (q1.y - q2.y) + q1.x * (q2.y - p1.y) + q2.x * (p1.y - q1.y));
    int area_t2_2x = abs(p1.x * (q2.y - q3.y) + q2.x * (q3.y - p1.y) + q3.x * (p1.y - q2.y));
    int area_t3_2x = abs(p1.x * (q3.y - q4.y) + q3.x * (q4.y - p1.y) + q4.x * (p1.y - q3.y));
    int area_t4_2x = abs(p1.x * (q1.y - q4.y) + q1.x * (q4.y - p1.y) + q4.x * (p1.y - q1.y));

    return area_t1_2x + area_t2_2x + area_t3_2x + area_t4_2x == 2 * area_rect;
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2){
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

}

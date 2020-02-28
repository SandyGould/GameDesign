#include "DisplayObjectContainer.h"

#include <algorithm>

DisplayObjectContainer::DisplayObjectContainer() : DisplayObject() {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(std::string id, std::string filepath) : DisplayObject(id, filepath) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(std::string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::~DisplayObjectContainer() {
    for (auto child : children) {
        delete child;
    }
}

void DisplayObjectContainer::addChild(DisplayObject* child) {
    children.push_back(child);
    child->parent = this; // make sure to include reverse reference also
    child->parentId = id;
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child) {
	auto it = std::find(this->children.cbegin(), this->children.cend(), child);
	if (it != this->children.cend()) {
        delete *it;
		this->children.erase(it);
	}
}

void DisplayObjectContainer::removeImmediateChild(std::string id) {
	auto it = std::find_if(this->children.cbegin(), this->children.cend(), [&](const auto child) { return child->id == id; });
	if (it != this->children.cend()) {
        delete *it;
		this->children.erase(it);
	}
}

void DisplayObjectContainer::removeChild(size_t index) {
    if (index < children.size()) {
        delete children[index];
        children.erase(children.begin() + index);
    }
}

void DisplayObjectContainer::removeThis() {
    if (this->parent != NULL) {
        ((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
    }
}

int DisplayObjectContainer::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
    if (index < 0 || index > numChildren()) {
        return NULL;
    }
    else return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(std::string id) {
    for (auto child : children) {
        if (child->id == id) {
            return child;
        }
    }
    return nullptr;
}

void DisplayObjectContainer::update(std::unordered_set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
    for (auto child : children) {
        child->update(pressedKeys);
    }
}

void DisplayObjectContainer::draw(AffineTransform& at) {
    DisplayObject::draw(at);
    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (auto child : children) {
        child->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}
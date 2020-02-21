#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include "DisplayObject.h"

#include <vector>
// #include "Event.h"
#include <string>
#include <algorithm>

class DisplayObjectContainer : public DisplayObject {

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(std::string id, std::string filepath);
	DisplayObjectContainer(std::string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(std::string id);
	void removeChild(size_t index);
	void removeThis();
	
	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(std::string id);

	void update(std::set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

	std::vector<DisplayObject*> children;
	std::vector<DisplayObject*> collisionList;
private:
	
	
};

#endif
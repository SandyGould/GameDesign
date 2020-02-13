#ifndef DISPLAYOBJECTCONTAINER_H
#define DISPLAYOBJECTCONTAINER_H

#include "DisplayObject.h"

#include <vector>
// #include "Event.h"
#include <string>

using namespace std;

class DisplayObjectContainer : public DisplayObject {

public:
	
	DisplayObjectContainer();
	DisplayObjectContainer(string id, string filepath);
	DisplayObjectContainer(string id, int red, int green, int blue);
	virtual ~DisplayObjectContainer();

	void addChild(DisplayObject* child);
	void removeImmediateChild(DisplayObject* child);
	void removeImmediateChild(string id);
	void removeChild(int index);
	void removeThis();
	
	virtual int numChildren();
	virtual DisplayObject* getChild(int index);
	virtual DisplayObject* getChild(string id);

	void update(set<SDL_Scancode> pressedKeys) override;
	void draw(AffineTransform& at) override;

	vector<DisplayObject*> children;
private:
	
	
};

#endif
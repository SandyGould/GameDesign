#pragma once

#include "../DisplayObject.h"

using namespace std;

class SelectionMenuBase : public DisplayObject {
public:
	SelectionMenuBase();
    SelectionMenuBase(const std::string& id);
};
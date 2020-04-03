#include "TweenableParams.h"

TweenableParams::TweenableParams() {
    this->key = "INVALID_KEY"; // only want use w/ prespecified params 
}

TweenableParams::TweenableParams(std::string key) { 
    this->key = key; 
}

TweenableParams::~TweenableParams() { }

std::string TweenableParams::getKey(){ 
    return this->key; 
}

// initialize instances for the enum
const TweenableParams TweenableParams::SCALE_X = TweenableParams("SCALE_X");
const TweenableParams TweenableParams::SCALE_Y = TweenableParams("SCALE_Y");
const TweenableParams TweenableParams::ALPHA = TweenableParams("ALPHA");
const TweenableParams TweenableParams::ROTATION = TweenableParams("ROTATION");
const TweenableParams TweenableParams::X = TweenableParams("X");
const TweenableParams TweenableParams::Y = TweenableParams("Y");
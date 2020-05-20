#pragma once

enum class TweenableParam {
    SCALE_X,
    SCALE_Y,
    ALPHA,
    ROTATION,
    X,
    Y,
};

enum class EaseType {
    LINEAR,
    EASE_IN,
    EASE_OUT,
    EASE_IN_OUT,
    EASE_OUT_IN,
};

// Object storing information relevant to one parameter being tweened.

class TweenParam { 
public:
    TweenParam(TweenableParam paramToTween,
               double startVal, double endVal,
               double startTime, double duration,
               EaseType easeType = EaseType::EASE_IN_OUT);

    TweenableParam getParam();
    double getStartVal();
    double getEndVal();
    double getStartTime();
    double getDuration();
    double getCurrVal();
    EaseType getEaseType();
    void setCurrVal(double value);
    void setCurrChange(double amountChange);
    bool isComplete();

private:
    TweenableParam paramToTween;
    double startVal;
    double endVal;
    double startTime;
    double duration;
    double currVal;
    EaseType easeType;
};

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

    [[nodiscard]] TweenableParam getParam() const;
    [[nodiscard]] double getStartVal() const;
    [[nodiscard]] double getEndVal() const;
    [[nodiscard]] double getStartTime() const;
    [[nodiscard]] double getDuration() const;
    [[nodiscard]] double getCurrVal() const;
    [[nodiscard]] EaseType getEaseType() const;

    void setCurrVal(double value);
    void setCurrChange(double amountChange);

    [[nodiscard]] bool isComplete() const;

private:
    TweenableParam paramToTween;
    double startVal;
    double endVal;
    double startTime;
    double duration;
    double currVal;
    EaseType easeType;
};

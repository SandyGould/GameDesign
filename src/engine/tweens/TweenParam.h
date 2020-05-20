#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include "TweenableParams.h"
#include <string>

// Object storing information relevant to one parameter being tweened.

class TweenParam { 
    public:
        inline static const std::string EASE_IN = "ease_in";
        inline static const std::string EASE_OUT = "ease_out";
        inline static const std::string EASE_IN_OUT = "ease_in_out";
        inline static const std::string EASE_OUT_IN = "ease_out_in";

        TweenParam(TweenableParams paramToTween,
                   double startVal, double endVal,
                   double startTime, double duration,
                   std::string easeType = TweenParam::EASE_IN_OUT);

        ~TweenParam();
        TweenableParams getParam();
        double getStartVal();
        double getEndVal();
        double getStartTime();
        double getDuration();
        double getCurrVal();
        std::string getEaseType();
        void setCurrVal(double value);
        void setCurrChange(double amountChange);
        bool isComplete();
    
    private:
        TweenableParams paramToTween;
        double startVal;
        double endVal;
        double startTime;
        double duration;
        double currVal;
        std::string easeType;
};

#endif

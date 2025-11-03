#pragma once

#include "Core.h"

namespace rpe {
    class RPE_API TimeStep {
    public:
        TimeStep(const float time = 0.0f) : time(time) {}

        float GetTimeS() const {return time;}
        float GetTimeMS() const {return time * 1000;}

        operator float() const {return time;}
    private:
        float time;
    };
}
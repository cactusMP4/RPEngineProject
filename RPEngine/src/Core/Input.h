#pragma once

#include "Core.h"

namespace rpe {
    class RPE_API Input {
    public:
        static bool IsKeyPressed(int key);

        static bool IsMouseButtonPressed(int button);
        static double GetMouseX();
        static double GetMouseY();
    };
}


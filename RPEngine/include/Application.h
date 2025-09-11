#pragma once
#include "Window.h"

namespace rpe {
    class Application {
    public:
        Application();
        virtual ~Application();
        void run();
    private:
        std::unique_ptr<Window> window;
        bool running = false;
    };
}


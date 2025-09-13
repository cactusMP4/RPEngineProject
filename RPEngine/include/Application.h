#pragma once

#include "Logger.h"
#include "Window.h"

namespace rpe {
    class Application {
    public:
        Application();
        virtual ~Application();
        void run();

        void onEvent(Event& event);
        bool onWindowClosed(WindowCloseEvent& event);
    private:
        std::unique_ptr<Window> window;
        bool running = false;
    };
}


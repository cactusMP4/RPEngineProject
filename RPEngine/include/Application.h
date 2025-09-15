#pragma once

#include "Core.h"
#include "Layer.h"
#include "Logger.h"
#include "Window.h"

namespace rpe {
    class RPE_API Application {
    public:
        Application();
        virtual ~Application();
        void run();

        void onEvent(Event& event);
        bool onWindowClosed(WindowCloseEvent& event);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer* overlay);
    private:
        std::unique_ptr<Window> window;
        bool running = false;
        LayerStack layers;
    };
}


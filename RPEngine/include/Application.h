#pragma once

#include "Core.h"
#include "Layer.h"
#include "Logger.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"

#define RPE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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

        Window& GetWindow() const { return *window; }
        static Application& GetApplication() { return *instance; }
    private:
        std::unique_ptr<Window> window;
        ImGuiLayer* imguiLayer;
        bool running = false;
        LayerStack layers;

        static Application* instance;
    };
}


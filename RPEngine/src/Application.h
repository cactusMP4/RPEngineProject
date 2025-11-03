#pragma once

#include "Core/Core.h"
#include "Core/Layer.h"
#include "Core/Logger.h"
#include "Render/Shader.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "Render/Buffer.h"
#include "Render/VertexArray.h"
#include "Render/Camera.h"

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
        static Application* instance;
        bool running = false;

        std::shared_ptr<Window> window;

        ImGuiLayer* imguiLayer;
        LayerStack layers;
    };
}


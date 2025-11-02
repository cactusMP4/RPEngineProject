#include "Application.h"

#include <memory>

#include "Input.h"
#include "Render/Camera.h"
#include "Render/Renderer.h"

namespace rpe {
    Application* Application::instance = nullptr;

    Application::Application() {
        RPE_CORE_INFO("Creating application");

        if (instance) {
            RPE_CORE_WARN("Application already exists");
            return;
        }
        instance = this;

        window = std::make_unique<Window>();
        window->Init();
        window->SetEventCallback(RPE_BIND_EVENT_FN(Application::onEvent));

        imguiLayer = new ImGuiLayer();
        PushOverlay(imguiLayer);
    }
    Application::~Application() {
        running = false;
    }

    void Application::onEvent(Event& event) {
        RPE_CORE_TRACE("Event: {0}", event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(RPE_BIND_EVENT_FN(Application::onWindowClosed));

        for (auto it = layers.end(); it != layers.begin(); ) {
            (*--it)->OnEvent(event);
            if (event.Handled) {
                //do not continue
                //(we don't want to shoot in FPS when we press a UI button for example)
                break;
            }
        }
    }

    void Application::run() {
        RPE_CORE_INFO("Running app...");

        running = true;
        while (running) {
            glClearColor(0.11f, 0.11f, 0.18f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            imguiLayer->Begin();
            for (Layer* layer : layers) {
                layer->Update();
                layer->RenderImGui();
            }
            imguiLayer->End();

            window->Update();
        }
    }
    bool Application::onWindowClosed(WindowCloseEvent &event) {
        RPE_CORE_INFO("Closing window. ");

        running = false;
        return true;
    }

    void Application::PushLayer(Layer *layer) {
        layers.PushLayer(layer);
    }
    void Application::PushOverlay(Layer *overlay) {
        layers.PushLayer(overlay);
    }
}

#include "Application.h"

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace rpe {
    Application::Application() {
        window = std::unique_ptr<Window>(new Window());
        window->SetEventCallback(BIND_EVENT_FN(Application::onEvent));
    }
    Application::~Application() {
        running = false;
    }

    void Application::onEvent(Event& event) {
        RPE_CORE_TRACE("Event: {0}", event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClosed));

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
        window->Init();
        running = true;
        while (running) {
            window->Update();

            for (Layer* layer : layers) {
                layer->Update();
            }
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
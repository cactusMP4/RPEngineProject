#include "Application.h"

#include "Input.h"

namespace rpe {
    Application* Application::instance = nullptr;

    Application::Application() {
        RPE_CORE_INFO("Creating application");

        if (Application::instance) {
            RPE_CORE_WARN("Application already exists");
            return;
        }

        Application::instance = this;

        window = std::unique_ptr<Window>(new Window());
        window->Init();
        window->SetEventCallback(RPE_BIND_EVENT_FN(Application::onEvent));
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
            window->Update();

            RPE_CORE_INFO("is F pressed: {0}", Input::IsKeyPressed(GLFW_KEY_F));
            RPE_CORE_INFO("is mouse 1 pressed: {0}", Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1));
            RPE_CORE_INFO("mouse pos: {0}, {1}", Input::GetMouseX(), Input::GetMouseY());

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
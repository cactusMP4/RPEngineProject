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
    }

    void Application::run() {
        window->Init();
        running = true;
        while (running) {
            window->Update();
        }
    }
    bool Application::onWindowClosed(WindowCloseEvent &event) {
        RPE_CORE_INFO("Closing window. ");

        running = false;
        return true;
    }

}
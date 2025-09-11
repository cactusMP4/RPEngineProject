//
// Created by cactus on 9/4/25.
//

#include "Application.h"

namespace rpe {
    Application::Application() {
        window = std::unique_ptr<Window>(new Window());
        window->Init();
    }
    Application::~Application() {
        window->Destroy();
    }

    void Application::run() {
        running = true;
        while (running) {
            window->Update();
        }
    }
}
#include "Window.h"

namespace rpe {
    void Window::Init() {
        if (!inited) {
            RPE_CORE_INFO("Initializing window '{0}' ({1}; {2})", title, width, height);

            if (const int success = glfwInit(); !success) {
                RPE_CORE_ERROR("Failed to initialize GLFW: {0}", success);
            }

            inited = true;

        } else {
            RPE_CORE_WARN("Window '{0}' already initialized", title);
        }

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            RPE_CORE_ERROR("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        glfwSwapInterval(1);
    }

    void Window::Update() const {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void Window::Destroy() const {
        glfwDestroyWindow(window);
    }
}


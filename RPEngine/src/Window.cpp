#include "Window.h"

namespace rpe {
    bool Window::Init() {
        if (!inited) {
            RPE_CORE_INFO("Initializing window '{0}' ({1}; {2})", title, width, height);

            if (const int success = glfwInit(); !success) {
                RPE_CORE_ERROR("Failed to initialize GLFW: {0}", success);
                return false;
            }

            inited = true;

        } else {
            RPE_CORE_WARN("Window '{0}' already initialized", title);
        }

        window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        glfwSwapInterval(1);

        return true;
    }

    void Window::Update() const {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}


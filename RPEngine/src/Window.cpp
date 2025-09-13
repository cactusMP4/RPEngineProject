#include "Window.h"

#include <utility>

int keyRepeatCounter = 0;

namespace rpe {
    Window::Window(std::string title, const int width, const int height) {
        data.title = std::move(title);
        data.width = width;
        data.height = height;
    }

    void Window::Init() {
        if (!data.inited) {
            if (const int success = glfwInit(); !success) {
                RPE_CORE_ERROR("Failed to initialize GLFW: {0}", success);
                return;
            }

            data.inited = true;

        } else {
            RPE_CORE_WARN("Window '{0}' already initialized", data.title);
            return;
        }

        glfwSetErrorCallback([](int code, const char* desc){
            RPE_CORE_ERROR("GLFW Error {0}: {1}", code, desc);
        });

        RPE_CORE_INFO("Initializing window '{0}' ({1}; {2})", data.title, data.width, data.height);
        window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            RPE_CORE_ERROR("Failed to create GLFW window");
            return;
        }
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, &data);
        glfwSwapInterval(1);

        //callbacks
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));

            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));

            if (action == GLFW_REPEAT) {
                keyRepeatCounter++;
            } else {
                keyRepeatCounter = 0;
            }

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, keyRepeatCounter);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                default: {
                    RPE_CORE_WARN("Unknown key action: {0}", action);
                }
            }
        });

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));

            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(xpos, ypos);
            data.eventCallback(event);
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xScroll, double yScroll) {
            windowData& data = *static_cast<windowData *>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(xScroll, yScroll);
            data.eventCallback(event);
        });
    }

    void Window::Update() const {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void Window::Destroy() const {
        glfwDestroyWindow(window);
    }
}


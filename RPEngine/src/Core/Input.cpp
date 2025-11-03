#include "Input.h"

#include "../Application.h"

namespace rpe {
    bool Input::IsKeyPressed(const int key) {
        GLFWwindow* window = Application::GetApplication().GetWindow().GetGLFWwindow();
        const int state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool Input::IsMouseButtonPressed(const int button) {
        GLFWwindow* window = Application::GetApplication().GetWindow().GetGLFWwindow();
        const int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }
    double Input::GetMouseX() {
        GLFWwindow* window = Application::GetApplication().GetWindow().GetGLFWwindow();
        double Xpos;
        glfwGetCursorPos(window, &Xpos, nullptr);

        return Xpos;
    }
    double Input::GetMouseY() {
        GLFWwindow* window = Application::GetApplication().GetWindow().GetGLFWwindow();
        double Ypos;
        glfwGetCursorPos(window, nullptr, &Ypos);

        return Ypos;
    }

}

#pragma once
#include "Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace rpe {
    class RPE_API OpenGLContext {
    public:
        OpenGLContext(GLFWwindow* window) : window(window) {};

        void Init();
        void SwapBuffers();
    private:
        GLFWwindow* window;
    };
}

#pragma once
#include "../Core.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace rpe {
    class RPE_API Context {
    public:
        Context(GLFWwindow* window) : window(window) {};

        void Init() const;
        void SwapBuffers() const;
    private:
        GLFWwindow* window;
    };
}

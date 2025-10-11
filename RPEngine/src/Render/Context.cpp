#include "Context.h"

#include "../Logger.h"

namespace rpe {
    void Context::Init() const {
        glfwMakeContextCurrent(window);
        if (const int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !success) {
            RPE_CORE_ERROR("Failed to initialize GLAD: {0}", success);
            return;
        }

        RPE_CORE_INFO("OpenGL info:");
        RPE_CORE_INFO("    Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        RPE_CORE_INFO("    Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        RPE_CORE_INFO("    Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }
    void Context::SwapBuffers() const {
        glfwSwapBuffers(window);
    }
}

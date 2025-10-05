#include "OpenGLContext.h"

#include "Logger.h"

namespace rpe {
    void OpenGLContext::Init() {
        glfwMakeContextCurrent(window);
        if (const int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); !success) {
            RPE_CORE_ERROR("Failed to initialize GLAD: {0}", success);
            return;
        }
    }
    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(window);
    }
}

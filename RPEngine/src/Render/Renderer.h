#pragma once

#include "VertexArray.h"
#include "../Core/Core.h"
#include "Camera.h"
#include "Shader.h"

namespace rpe {
    class RPE_API Renderer {
    public:
        static void BeginScene(const Camera& camera);
        static void EndScene();

        static void Submit(
            const std::shared_ptr<VertexArray>& vertex_array,
            const std::shared_ptr<Shader>& shader,
            const Transform& transform = Transform()
        );
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* data;
    };
}

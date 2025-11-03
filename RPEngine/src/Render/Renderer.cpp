#include "Renderer.h"

namespace rpe {
    Renderer::SceneData* Renderer::data = new SceneData;
    void Renderer::BeginScene(const Camera& camera) {
        data->ViewProjectionMatrix = camera.GetViewProjMatrix();
    }
    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniform("u_ViewProjMat", data->ViewProjectionMatrix);
        shader->UploadUniform("u_TransformMat", transform);

        vertex_array->Bind();
        const auto count = static_cast<GLsizei>(vertex_array->GetIndexBuffer()->GetCount());
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}

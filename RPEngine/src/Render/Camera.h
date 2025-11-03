#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Application.h"
#include "../Core/Transform.h"

namespace rpe {
    enum class CameraProjection {Orthographic, Perspective};

    class Camera {
    public:
        Camera(
            const float fov = 65,
            const float viewDistance = 1000,
            const CameraProjection perspective = CameraProjection::Perspective
        ) : FOV(fov), viewDistance(viewDistance), projection(perspective) {
            const Window& window = Application::GetApplication().GetWindow();
            aspectRatio = static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight());
        }

        void SetFov(const float fov) {FOV = fov;}
        void SetAspectRatio(const float ar) {aspectRatio = ar;}
        void SetViewDistance(const float distance) {viewDistance = distance;}

        void SetPerspective(const CameraProjection proj) {projection = proj;}


        Transform& GetTransform() { return transform; }

        float GetFov() const { return FOV; }
        float GetAspectRatio() const { return aspectRatio; }
        float GetViewDistance() const { return viewDistance; }

        CameraProjection GetProjection() const { return projection; }

        glm::mat4 GetViewMatrix() const {
            return glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetLookDir(), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        glm::mat4 GetProjectionMatrix() const {
            switch (projection) {
                case CameraProjection::Orthographic:
                    return glm::ortho(-1.0f, 1.0f, -1.0f/aspectRatio, 1.0f/aspectRatio, 0.0f, viewDistance);
                case CameraProjection::Perspective:
                    return glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, viewDistance);
            }

            RPE_CORE_ERROR("Unknown projection type!");
            return {1.0f};
        }

        glm::mat4 GetViewProjMatrix() const {
            return GetProjectionMatrix() * GetViewMatrix();
        }
    private:
        Transform transform;

        float FOV;
        float aspectRatio;
        float viewDistance;

        CameraProjection projection;
    };
}

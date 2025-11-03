#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Application.h"

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

        void SetPosition(const glm::vec3 &pos) {position = pos;}
        void SetLookDir(const glm::vec3 &dir) {lookDir = glm::normalize(dir);}

        void SetFov(const float fov) {FOV = fov;}
        void SetAspectRatio(const float ar) {aspectRatio = ar;}
        void SetViewDistance(const float distance) {viewDistance = distance;}

        void SetPerspective(const CameraProjection proj) {projection = proj;}


        const glm::vec3& GetPosition() const { return position; }
        const glm::vec3& GetLookDir() const { return lookDir; }

        float GetFov() const { return FOV; }
        float GetAspectRatio() const { return aspectRatio; }
        float GetViewDistance() const { return viewDistance; }

        CameraProjection GetProjection() const { return projection; }


        void Move(const glm::vec3 &pos) {position += pos;}


        glm::mat4 GetViewMatrix() const {
            return glm::lookAt(position, position + lookDir, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        glm::mat4 GetProjectionMatrix() const {
            switch (projection) {
                case CameraProjection::Orthographic:
                    return glm::ortho(-1.0f, 1.0f, -1.0f/aspectRatio, 1.0f/aspectRatio, 0.0f, viewDistance);
                case CameraProjection::Perspective:
                    return glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, viewDistance);
            }
        }

        glm::mat4 GetViewProjMatrix() const {
            return GetProjectionMatrix() * GetViewMatrix();
        }
    private:
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 lookDir = glm::vec3(0, 0, -1);

        float FOV;
        float aspectRatio;
        float viewDistance;

        CameraProjection projection;
    };
}

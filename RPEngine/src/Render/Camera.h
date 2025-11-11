#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Application.h"
#include "../Core/Transform.h"

namespace rpe {
    enum class CameraProjection {Orthographic, Perspective};

    class RPE_API Camera {
    public:
        Camera(
            const float fov = 65,
            const float viewDistance = 1000,
            const CameraProjection perspective = CameraProjection::Perspective
        );

        void SetFov(const float fov);
        void SetAspectRatio(const float ar);
        void SetViewDistance(const float distance);
        void SetProjection(const CameraProjection proj);

        Transform& GetTransform();
        float GetFov() const;
        float GetAspectRatio() const;
        float GetViewDistance() const;
        CameraProjection GetProjection() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewProjMatrix() const;
    private:
        Transform transform;

        float FOV;
        float aspectRatio;
        float viewDistance;

        CameraProjection projection;
    };
}

#pragma once

#include "Core.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace rpe {
    class RPE_API Transform {
    public:
        Transform(
            const glm::vec3& position = glm::vec3(0.0f),
            const glm::vec3& lookDir = glm::vec3(0.0f, 0.0f, -1.0f),
            const glm::vec3& scale = glm::vec3(1.0f)
        ) : position(position), lookDir(lookDir), scale(scale) {}

        glm::vec3 GetPosition() const { return position; }
        glm::vec3 GetLookDir() const { return lookDir; }
        glm::vec3 GetScale() const { return scale; }

        glm::mat4 GetTransformMat() const {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

            // rotation here?

            transform = glm::scale(transform, scale);

            return transform;
        }

        void SetPosition(const glm::vec3 &pos) {position = pos;}
        void SetLookDir(const glm::vec3 &dir) {lookDir = dir;}
        void SetScale(const glm::vec3 &s) {scale = s;}

        void Move(const glm::vec3 &pos) {position += pos;}
        void Scale(const glm::vec3 &s) {scale *= s;}
    private:
        glm::vec3 position, lookDir, scale;
    };
}

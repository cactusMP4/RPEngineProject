#pragma once

#include "../Core.h"
#include "glm/fwd.hpp"

namespace rpe {
    class RPE_API Shader {
    public:
        Shader(const std::string& filePath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniform(const std::string& name, const glm::mat4& matrix) const;
    private:
        unsigned int renderID;
    };
}

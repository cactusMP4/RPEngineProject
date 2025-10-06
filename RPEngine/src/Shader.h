#pragma once

namespace rpe {
    class Shader {
    public:
        Shader(const std::string& filePath);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned int renderID;
    };
}

#pragma once

namespace rpe {
    class VertexBuffer {
    public:
        VertexBuffer(const float* vertices, unsigned int size);
        ~VertexBuffer();

        void Bind() const;
    private:
        unsigned int rendererID{};
    };

    class IndexBuffer {
    public:
        IndexBuffer(const unsigned int* indices, unsigned int count);
        ~IndexBuffer();

        void Bind() const;

        unsigned int GetCount() const {return count;};
    private:
        unsigned int rendererID{};
        unsigned int count;
    };
}
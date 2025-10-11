#include "Buffer.h"

#include "imstb_truetype.h"
#include "glad/glad.h"

namespace rpe {
    //vertex
    VertexBuffer::VertexBuffer(const float* vertices, unsigned int size) {
        glGenBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &rendererID);
    }
    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    //indices
    IndexBuffer::IndexBuffer(const unsigned int *indices, unsigned int count) : count(count) {
        glGenBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }
    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &rendererID);
    }
    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

}
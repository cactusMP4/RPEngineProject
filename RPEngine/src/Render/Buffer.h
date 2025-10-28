#pragma once

#include "BufferLayout.h"

namespace rpe {
    class RPE_API VertexBuffer {
    public:
        VertexBuffer(const float* vertices, unsigned int size);
        ~VertexBuffer();

		const BufferLayout& GetLayout() const { return layout; }
		void SetLayout(BufferLayout& newLayout) { layout = newLayout; }

        void Bind() const;
    private:
        unsigned int rendererID{};
		BufferLayout layout;
    };

    class RPE_API IndexBuffer {
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
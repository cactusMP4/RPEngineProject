#include "VertexArray.h"

namespace rpe {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &rendererID);
		glBindVertexArray(rendererID);
	}
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &rendererID);
	}
	void VertexArray::Bind() const {
		glBindVertexArray(rendererID);
	}
	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}
	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		const BufferLayout& layout = vertexBuffer->GetLayout();

		if (layout.GetElements().size() == 0) {
			RPE_CORE_WARN("Vertex layout has no elements!");
			RPE_CORE_WARN("Make sure to set the layout of the VertexBuffer before adding it to the VertexArray!");
			return;
		}

		int index = 0;
		for (const BufferElement& element : layout.GetElements()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				static_cast<GLint>(element.GetComponentCount()),
				element.GetGLenumType(),
				element.normalized,
				static_cast<GLsizei>(layout.GetStride()),
				(const void*)element.offset
			);
			index++;
		}
		vertexBuffers.push_back(vertexBuffer);
	}
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(rendererID);
		indexBuffer->Bind();
		this->indexBuffer = indexBuffer;
	}
}
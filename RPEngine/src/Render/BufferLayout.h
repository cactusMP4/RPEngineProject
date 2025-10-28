#pragma once

#include "../Logger.h"
#include <glad/glad.h>

namespace rpe {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};
	static unsigned int ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}
		RPE_CORE_ERROR("Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		unsigned int offset;
		unsigned int size;
		bool normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) :
			name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {

		}

		unsigned int GetComponentCount() const {
			switch (type) {
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
			}

			RPE_CORE_ERROR("Unknown ShaderDataType");
			return 0;
		}
		GLenum GetGLenumType() const {
			switch (type) {
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			}

			RPE_CORE_ERROR("Unknown ShaderDataType");
			return 0;
		}
	};
	class BufferLayout {
	public:
		BufferLayout() {};

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements) {
			CalculateOffsetsAndStride();
		};

		const std::vector<BufferElement>& GetElements() const { return elements; }
		unsigned int GetStride() const { return stride; }
	private:
		std::vector<BufferElement> elements;
		unsigned int stride = 0;

		void CalculateOffsetsAndStride() {
			unsigned int offset = 0;
			stride = 0;
			for (auto& element : elements) {
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	};
}
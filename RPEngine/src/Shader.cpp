#include "Shader.h"

#include <fstream>
#include <glad/glad.h>

#include "Logger.h"

namespace rpe {
    Shader::Shader(const std::string& filePath) {
        std::string vertexSrc, fragmentSrc;

        std::ifstream shaderFile(filePath);

        std::string line;
        bool readingVertex = true;
        while (std::getline(shaderFile, line)) {
            if (line == "#type vertex") {
                readingVertex = true;
            } else if (line == "#type fragment") {
                readingVertex = false;
            } else {
                if (readingVertex) {
                    vertexSrc += line + "\n";
                } else {
                    fragmentSrc += line + "\n";
                }
            }
        }
        RPE_CORE_INFO("created shader: ");
        RPE_CORE_INFO("vertex: \n{0}", vertexSrc);
        RPE_CORE_INFO("fragment: \n{0}", fragmentSrc);


        ///stolen code from https://wikis.khronos.org/opengl/Shader_Compilation#Example:

        // Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar *source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			RPE_CORE_FATAL("Failed to compile vertex shader:\n{0}", infoLog.data());
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, nullptr);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			RPE_CORE_FATAL("Failed to compile fragment shader:\n{0}", infoLog.data());
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		renderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(renderID, vertexShader);
		glAttachShader(renderID, fragmentShader);

		// Link our program
		glLinkProgram(renderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(renderID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(renderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(renderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(renderID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			RPE_CORE_FATAL("failed to link shader:\n{0}", infoLog.data());
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(renderID, vertexShader);
		glDetachShader(renderID, fragmentShader);
    }
	Shader::~Shader() {
		glDeleteProgram(renderID);
	}
	void Shader::Bind() const{
		glUseProgram(renderID);
	}
	void Shader::Unbind() const{
		glUseProgram(0);
    }
}

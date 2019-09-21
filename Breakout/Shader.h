#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader
{
public:
	Shader() = default;
	Shader(const GLchar* vertexSource, const GLchar *fragmentSource, const GLchar* geometrySource = nullptr);
	Shader& Use();
	void Compile(const GLchar* vertexSource, const GLchar *fragmentSource, const GLchar* geometrySource = nullptr);

	GLuint ID;
private:
	void checkForCompileErrors(GLuint Object, std::string type);

	// Compile a single shader
	void CompileShader(GLenum shaderType, const GLchar * vertexSource, std::string type, GLuint & shader);

private:
};


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

	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
	void checkForCompileErrors(GLuint Object, std::string type);

	// Compile a single shader
	void CompileShader(GLenum shaderType, const GLchar * vertexSource, std::string type, GLuint & shader);
};


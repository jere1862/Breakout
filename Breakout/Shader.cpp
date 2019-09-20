#include "Shader.h"
#include <iostream>

Shader & Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource)
{
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint geometryShader = 0;

	this->ID = glCreateProgram();

	compileShader(GL_VERTEX_SHADER, vertexSource, "VERTEX", vertexShader);
	compileShader(GL_FRAGMENT_SHADER, fragmentSource, "FRAGMENT", fragmentShader);

	if (geometrySource)
	{
		compileShader(GL_GEOMETRY_SHADER, geometrySource, "GEOMETRY", geometryShader);
		glAttachShader(this->ID, geometryShader);
	}

	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);

	glLinkProgram(this->ID);
	checkForCompileErrors(this->ID, "PROGRAM");

	if (geometrySource)
	{
		glDeleteShader(geometryShader);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkForCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}

void Shader::compileShader(GLenum shaderType, const GLchar* vertexSource, std::string type, GLuint& shader)
{
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &vertexSource, NULL);
	glCompileShader(shader);
	checkForCompileErrors(shader, type);
}
#pragma once

#include "glad/glad.h"

class Texture
{
public:
	Texture();

	Texture(GLuint width, GLuint height, GLuint internalFormat, unsigned char* data);
	
	void Generate(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;

	GLuint ID;
private:
	
	GLuint Width;
	GLuint Height;

	GLuint InternalFormat;
	GLuint ImageFormat;

	GLuint WrapS;
	GLuint WrapT;
	GLuint FilterMin;
	GLuint FilterMax;
};


#include "Texture.h"
#include <iostream>

Texture::Texture()
	: Width(0)
	, Height(0)
	, InternalFormat(GL_RGB)
	, ImageFormat(GL_RGB)
	, WrapS(GL_REPEAT)
	, WrapT(GL_REPEAT)
	, FilterMin(GL_LINEAR)
	, FilterMax(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

Texture::Texture(GLuint width, GLuint height, GLuint internalFormat, unsigned char* data)
	: Width(width)
	, Height(height)
	, InternalFormat(internalFormat)
	, ImageFormat(internalFormat)
	, WrapS(GL_REPEAT)
	, WrapT(GL_REPEAT)
	, FilterMin(GL_LINEAR)
	, FilterMax(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
	this->Generate(this->Width, this->Height, data);
}

void Texture::Generate(GLuint width, GLuint height, unsigned char* data)
{
	this->Width = width;
	this->Height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, this->Width, this->Height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->WrapT);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->FilterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->FilterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

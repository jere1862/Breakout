#include "ResourceManager.h"
#include <SOIL.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Texture> ResourceManager::CachedTextures;
std::map<std::string, Shader> ResourceManager::CachedShaders;

Texture ResourceManager::GetTexture(const std::string& name)
{
	return CachedTextures[name];
}

Shader ResourceManager::GetShader(const std::string& name)
{
	return CachedShaders[name];
}

Shader ResourceManager::LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile, const GLchar* geometryShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		// Read code file, stream it to a string
		std::ifstream vertexShaderFile(vertexShaderFile);
		std::ifstream fragmentShaderFile(fragmentShaderFile);

		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();

		if (geometryShaderFile)
		{
			std::ifstream geometryShaderFile(geometryShaderFile);
			std::stringstream geometryShaderStream;
			geometryShaderStream << geometryShaderFile.rdbuf();
			geometryCode = geometryShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files." << std::endl;
	}

	return Shader(vertexCode.c_str(), fragmentCode.c_str(), geometryCode.length() == 0 ? nullptr : geometryCode.c_str());
}

Texture ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha)
{
	GLuint textureFormat = GL_RGB;
	GLuint soilFormat = SOIL_LOAD_RGB;

	if (alpha)
	{
		textureFormat = GL_RGBA;
		soilFormat = SOIL_LOAD_RGBA;
	}

	int height;
	int width;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, soilFormat);

	Texture texture(width, height, textureFormat, image);

	SOIL_free_image_data(image);

	return texture;
}

void ResourceManager::Clear()
{
	for (const auto& it : CachedTextures)
	{
		glDeleteTextures(1, &it.second.ID);
	}
	for (const auto& it : CachedShaders)
	{
		glDeleteProgram(it.second.ID);
	}
}

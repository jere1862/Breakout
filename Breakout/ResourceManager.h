#pragma once

#include "glad/glad.h"
#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"

class ResourceManager
{
public:
	
	static Texture GetTexture(const std::string& fileName);
	static Shader GetShader(const std::string& fileName);
	
	static Shader LoadShader(const GLchar* vertexShaderFile, const GLchar* fragmentShaderFile, const GLchar* geometryShaderFile = nullptr);
	static Texture LoadTexture(const GLchar* file, GLboolean alpha);

	static void Clear();

private:
	static std::map<std::string, Texture> CachedTextures;
	static std::map<std::string, Shader> CachedShaders;
};


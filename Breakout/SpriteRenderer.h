#pragma once

#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>

class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();

	void Draw(const Texture & texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color);

private:
	void initRenderData();

private:
	Shader textureShader;
	GLuint quadVAO;
};


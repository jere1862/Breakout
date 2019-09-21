#pragma once
#include "Shader.h"

class TriangleRenderer
{
public:
	TriangleRenderer(const Shader& shader);
	TriangleRenderer();
	void Draw();

private:
	Shader triangleShader;
	GLuint triangleVAO;
};


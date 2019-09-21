#include "TriangleRenderer.h"
#include "ResourceManager.h"

TriangleRenderer::TriangleRenderer(const Shader& shader)
	: triangleShader(shader)
{
	GLuint VBO;

	glGenVertexArrays(1, &triangleVAO);
	glGenBuffers(1, &VBO);

	// 1. Bind vertex array object
	glBindVertexArray(triangleVAO);

	// 2. Copy vertices in a buffer for OpenGL to use
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3. Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

TriangleRenderer::TriangleRenderer()
{
	glDeleteVertexArrays(1, &triangleVAO);
}


void TriangleRenderer::Draw()
{
	triangleShader.Use();
	glBindVertexArray(triangleVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
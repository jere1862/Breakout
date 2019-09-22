#include "SpriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(const Shader& shader)
	: textureShader(shader)
{
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::Draw(const Texture& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	// Prepare transformations
	textureShader.Use();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	// Move origin of rotation to center
	model = glm::translate(model, glm::vec3(position.x + size.x * 0.5, position.y + size.y * 0.5, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(position.x - size.x * 0.5, position.y - size.y * 0.5, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	textureShader.SetMatrix4("model", model);
	textureShader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;

	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	// Initialize buffer and vertex array
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	// Initialize the VBO data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindVertexArray(quadVAO);
	// Associate the VAO with the VBO.
	glEnableVertexAttribArray(0);
	// Describe the vertex data to opengl
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	
	// Unbind the array buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

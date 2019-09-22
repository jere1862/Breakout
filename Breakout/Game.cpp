#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "glm/glm.hpp"
#include "SpriteRenderer.h"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(GLuint height, GLuint width)
	: height(height)
	, width(width)
{
}


void Game::Init()
{
	Shader shader = ResourceManager::LoadShader("sprite", "SpriteVertex.glsl", "SpriteFragment.glsl");
	Texture img = ResourceManager::LoadTexture("wood", "Images/Wood.png", GL_FALSE);

	spriteRenderer = std::make_unique<SpriteRenderer>(shader);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	Shader& spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use().SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
	spriteRenderer->Draw(ResourceManager::GetTexture("wood"), glm::vec2(20.0f, 0.0f), glm::vec2(100, 200), 0, glm::vec3(1.0f, 1.0f, 1.0f));
}

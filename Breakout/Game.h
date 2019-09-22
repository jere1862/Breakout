#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	Game(GLuint height, GLuint width);
	GLboolean Keys[1024];
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	GameState State;

private:
	GLuint height;
	GLuint width;
	std::unique_ptr<class SpriteRenderer> spriteRenderer;
};


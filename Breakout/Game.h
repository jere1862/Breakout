#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	~Game();

private:
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

private:
	GameState State;
};


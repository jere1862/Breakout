#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Game.h"
#include "ResourceManager.h"
#include "TriangleRenderer.h"

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_HEIGHT, SCREEN_WIDTH);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR:GLAD: Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, keyCallback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Breakout.Init();

	GLdouble deltaTime = 0.0f;
	GLdouble lastFrame = 0.0f;

	Breakout.State = GAME_ACTIVE;

	Shader shader = ResourceManager::LoadShader("TriangleVertexShader.glsl", "TriangleFragmentShader.glsl");
	TriangleRenderer triangle(shader);
	
	// ------------

	while (!glfwWindowShouldClose(window))
	{
		GLdouble currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Input Processing
		Breakout.ProcessInput(deltaTime);

		// Render
		glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle
		triangle.Draw();
		// end test code

		Breakout.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ResourceManager::Clear();
	glfwTerminate();

	return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}
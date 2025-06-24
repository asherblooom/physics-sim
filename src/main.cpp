#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <physics-sim/game.hpp>
#include <physics-sim/resource_manager.hpp>
#include "glm/detail/func_matrix.hpp"
#include "glm/detail/type_mat.hpp"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
const glm::vec2 getMousePos(GLFWwindow* window);

Game* physSim = new Game(SCR_WIDTH, SCR_HEIGHT);

int main() {
	// Initialise glfw and set options
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Physics Sim", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialise GLAD - manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		glfwTerminate();
		return -1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set initial viewport
	framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	physSim->Init();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Event loop
	while (!glfwWindowShouldClose(window)) {
		// calculate delta time
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// manage user input
		// -----------------
		physSim->ProcessInput(deltaTime);

		// update game state
		// -----------------
		physSim->MousePos = getMousePos(window);
		physSim->Update(deltaTime);

		// render
		// ------
		glClearColor(0.298, 0.831, 0.941, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		physSim->Render();

		glfwSwapBuffers(window);
	}
	delete physSim;
	glfwTerminate();
	return 0;
}

// callback for updating window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	float gameAspectRatio = 16.0f / 9.0f;
	float windowAspectRatio = float(width) / float(height);
	if (windowAspectRatio < gameAspectRatio) {
		// need black bars top and bottom to preserve game aspect ratio
		float heightRange = width * (1 / gameAspectRatio);
		float heightOffset = (height - heightRange) / 2;
		glViewport(0, heightOffset, width, height - heightOffset * 2);

	} else if (windowAspectRatio > gameAspectRatio) {
		// need black bars left and right to preserve game aspect ratio
		float widthRange = height * gameAspectRatio;
		float widthOffset = (width - widthRange) / 2;
		glViewport(widthOffset, 0, width - widthOffset * 2, height);

	} else
		glViewport(0, 0, width, height);
}

// callback for processing input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			physSim->Keys[key] = true;
		else if (action == GLFW_RELEASE)
			physSim->Keys[key] = false;
	}
}

const glm::vec2 getMousePos(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// Get cursor coordinates relative to the window's top-left corner.
	double relativeCursorX, relativeCursorY;
	glfwGetCursorPos(window, &relativeCursorX, &relativeCursorY);
	auto cursorPos = glm::vec2(relativeCursorX, relativeCursorY);

	//TODO: fixme
	//transform coordinates from screen space into world space
	glm::mat4 projection = glm::ortho(0.0f, (float)(width), (float)(height), 0.0f, -1.0f, 1.0f);
	auto projectionInv = glm::inverse(projection);
	glm::vec4 transformedCursor = projectionInv * glm::vec4(cursorPos.x, cursorPos.y, 0, 1);

	// return glm::vec2(absoluteCursorX, absoluteCursorY);
	return glm::vec2(transformedCursor.x, transformedCursor.y);
}

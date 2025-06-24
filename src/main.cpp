#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <physics-sim/game.hpp>

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

// calculates the boundaries of the screen space needed to maintain a constant aspect ratio and keep everything displayed
auto calculateRenderBounds(int windowWidth, int windowHeight) {
	struct bounds {
		float x;
		float y;
		float width;
		float height;
	};
	float gameAspectRatio = 16.0f / 9.0f;
	float windowAspectRatio = float(windowWidth) / float(windowHeight);
	if (windowAspectRatio < gameAspectRatio) {
		// need black bars top and bottom to preserve game aspect ratio
		float heightRange = windowWidth * (1 / gameAspectRatio);
		float heightOffset = (windowHeight - heightRange) / 2;
		return bounds{0, heightOffset, (float)windowWidth, windowHeight - heightOffset * 2};

	} else if (windowAspectRatio > gameAspectRatio) {
		// need black bars left and right to preserve game aspect ratio
		float widthRange = windowHeight * gameAspectRatio;
		float widthOffset = (windowWidth - widthRange) / 2;
		return bounds{widthOffset, 0, windowWidth - widthOffset * 2, (float)windowHeight};

	} else
		return bounds{0, 0, (float)windowWidth, (float)windowHeight};
}

// callback for updating window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	auto [x, y, gameWidth, gameHeight] = calculateRenderBounds(width, height);
	glViewport(x, y, gameWidth, gameHeight);
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
	auto [x, y, gameWidth, gameHeight] = calculateRenderBounds(width, height);

	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);

	//transform coordinates from screen space into world space

	//move top left to match beginning of render area
	cursorX = cursorX - x;
	cursorY = cursorY - y;

	//we know world space has coordinates (0, 0) to (1920, 1080)
	double xRatio = 1920.0 / gameWidth;
	double yRatio = 1080.0 / gameHeight;

	return glm::vec2(cursorX * xRatio, cursorY * yRatio);
}

#ifndef GAME_HPP
#define GAME_HPP

#include "game_object.hpp"
#include "render/sprite_renderer.hpp"
#include "resource_manager.hpp"

#include <GLFW/glfw3.h>
#include <vector>

class Game {
private:
	// the max values in the coordinate system for x and y respectively
	unsigned int width, height;
	// this is a pointer so that we can choose when to destruct it (that is, before glfwTerminate is called)
	SpriteRenderer* renderer;

	std::vector<GameObject> balls;
	// stores indicies of GameObjects in balls in sorted order, used for quicker sorting and making sure selectedBall always points to the same object
	std::vector<uint> ballsIndex;
	// stores a pointer to the ball in the balls vector when said ball is hovered over
	// set to nullptr if no ball is hovered over
	GameObject* selectedBall = nullptr;
	std::vector<GameObject> container;

	GameObject& makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity);
	std::vector<CollisionInfo> sweepAndPruneCollisions(std::vector<GameObject>& balls, std::vector<GameObject>& container);

public:
	bool Keys[1024];
	bool MouseButtons[3];
	glm::vec2 MousePos;
	glm::vec2 ChangeInMousePos;
	Game(unsigned int width, unsigned int height);
	~Game() {
		delete renderer;
		ResourceManager::Clear();
	}
	// initialize game state (load all shaders/textures/levels)
	void Init();
	// game loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

#endif

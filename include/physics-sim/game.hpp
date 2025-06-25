#ifndef GAME_HPP
#define GAME_HPP

#include <physics-sim/ball.hpp>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>
#include <physics-sim/sprite_renderer.hpp>

#include <GLFW/glfw3.h>
#include <memory>
#include <optional>
#include <vector>

class Game {
private:
	// the max values in the coordinate system for x and y respectively
	unsigned int width, height;
	SpriteRenderer* renderer;
	std::vector<Ball> balls;
	std::unique_ptr<PhysObject> container;
	// the vector stores the colour of the ball (as when selected is it re-coloured white)
	std::optional<Ball*> selectedBall;

	PhysObject& makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity);

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

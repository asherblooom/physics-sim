#ifndef GAME_HPP
#define GAME_HPP

#include <physics-sim/object_manager.hpp>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>
#include <physics-sim/sprite_renderer.hpp>

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class Game {
private:
	unsigned int width, height;
	SpriteRenderer* renderer;
	std::vector<std::unique_ptr<PhysObject>> balls;
	std::unique_ptr<PhysObject> container;

	PhysObject& makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity);

public:
	bool Keys[1024];
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

#ifndef GAME_HPP
#define GAME_HPP

#include <physics-sim/ball.hpp>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>
#include <physics-sim/sprite_renderer.hpp>

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

// TODO: encapsulate this better - in seperate PhysicsEngine class?
struct CollisionPoints {
	glm::vec2 A;	   // Furthest point of A into B
	glm::vec2 B;	   // Furthest point of B into A
	glm::vec2 Normal;  // B – A normalized
	float Depth;	   // Length of B – A
	bool HasCollision;
};

class Game {
   private:
	// the max values in the coordinate system for x and y respectively
	unsigned int width, height;
	// this is a pointer so that we can choose when to destruct it (that is, before glfwTerminate is called)
	SpriteRenderer* renderer;
	std::vector<Ball> balls;
	std::unique_ptr<PhysObject> container;
	// stores a pointer to the ball in the balls vector when said ball is hovered over
	// set to nullptr if no ball is hovered over
	Ball* selectedBall;

	PhysObject& makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity);

	// FIXME: AHHHHHHHHH
	// (from https://winter.dev/articles/physics-engine)

   public:
	//Physics constants
	static constexpr glm::vec2 gravity = {0, -9.81};

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

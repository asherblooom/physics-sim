#include <physics-sim/ball.hpp>
#include "physics-sim/resource_manager.hpp"

Ball::Ball(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{pos,
				 glm::vec2(100, 100),
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity} {}

#include <physics-sim/ball.hpp>
#include <physics-sim/resource_manager.hpp>

#include <cmath>

Ball::Ball(glm::vec2 pos, float diameter, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{pos, (float)diameter * glm::vec2(50, 50), ResourceManager::GetTexture("ball"), color, velocity}, Radius{diameter / 2.0f} {}

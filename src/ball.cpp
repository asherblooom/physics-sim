#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>

Ball::Ball(glm::vec2 center, float diameter, float mass, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{center,
				 diameter * glm::vec2(50),
				 mass,
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity},
	  Radius{diameter / 2.0f} {}

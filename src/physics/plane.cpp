#include "../resource_manager.hpp"
#include "phys_object.hpp"

Plane::Plane(glm::vec2 center, glm::vec2 normal, float length, glm::vec3 color)
	: PhysObject{center,
				 {length, length * (1080.0f / 1920.0f)},
				 0,
				 ResourceManager::GetTexture("plane"),
				 color,
				 glm::vec2(0)},
	  Normal{normal},
	  Length{length} {}

CollisionPoints Plane::CollideWithBall(Ball &b) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

CollisionPoints Plane::CollideWithPlane(Plane &p) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

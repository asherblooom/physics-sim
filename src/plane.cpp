#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>

Plane::Plane(glm::vec2 center, glm::vec2 normal, float length, glm::vec3 color)
	: PhysObject{center,
				 {length, length * (1080.0f / 1920.0f)},
				 0,
				 ResourceManager::GetTexture("plane"),
				 color,
				 glm::vec2(0)},
	  Normal{normal},
	  Length{length} {}

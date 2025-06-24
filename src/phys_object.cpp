#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: GameObject{pos, size, texture, color}, velocity(velocity), force(glm::vec2(0, 0)) {}

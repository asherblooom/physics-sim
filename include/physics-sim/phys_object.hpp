#ifndef PHYSOBJECT_HPP
#define PHYSOBJECT_HPP

#include <glm/glm.hpp>

#include <physics-sim/game_object.hpp>
#include <physics-sim/texture.hpp>

// an object that can be manipulated by the physics engine
class PhysObject : public GameObject {
public:
	void AddForce(glm::vec2 force) { this->force += force; }
	PhysObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f),
			   glm::vec2 velocity = glm::vec2(0.0f));

protected:
	glm::vec2 velocity, force;
};

#endif

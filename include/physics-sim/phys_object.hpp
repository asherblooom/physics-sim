#ifndef PHYSOBJECT_HPP
#define PHYSOBJECT_HPP

#include <glm/glm.hpp>

#include <physics-sim/game_object.hpp>
#include <physics-sim/texture.hpp>

// an object that can be manipulated by the physics engine
class PhysObject : public GameObject {
public:
	glm::vec2 Center;
	const float MassInv;

	PhysObject(glm::vec2 center, glm::vec2 size, float mass, Texture2D texture, glm::vec3 color = glm::vec3(1.0f),
			   glm::vec2 velocity = glm::vec2(0.0f));

	void AddForce(glm::vec2 force) { this->force += force; }
	void ResolveForces(float dt);
	void ClearForces() { force = glm::vec3(0); }

	void ClearVelocity() { velocity = glm::vec3(0); }

protected:
	glm::vec2 velocity, force;
};

#endif

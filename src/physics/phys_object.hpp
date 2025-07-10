#ifndef PHYSOBJECT_HPP
#define PHYSOBJECT_HPP

#include <glm/glm.hpp>

#include "../transform.hpp"

class GameObject;

//TODO: move this somewhere else???
struct CollisionInfo {
	GameObject* A;
	GameObject* B;
	CollisionPoints points;
};

// a general object that can be manipulated by the physics engine
class PhysObject {
public:
	float Mass;

	PhysObject(Transform& parentTransform, float mass, glm::vec2 velocity);

	void AddForce(glm::vec2 force) {
		this->force.x += force.x;
		// down is +ve y, up is moving towards y=0 (so -ve y)
		this->force.y += -force.y;
	}
	// will update position based on forces added
	void ResolveForces(float dt);
	void ClearForces() { force = glm::vec3(0); }
	void ClearVelocity() { velocity = glm::vec3(0); }

private:
	glm::vec2 velocity, force;
	Transform& transform;
};

#endif

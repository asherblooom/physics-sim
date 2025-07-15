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
	// stores 1/Mass for quicker calculations
	float InverseMass;
	bool HasGravity = true;
	// a static object never moves but can be collided with
	bool Static = false;

	PhysObject(Transform& parentTransform, float mass, glm::vec2 velocity);

	void AddForce(glm::vec2 force);

	// will update position based on forces added
	// contains default values for gravity and damping
	void ResolveForces(float dt, glm::vec2 gravity = {0, -9.81}, float dampingFactor = 0.9f);

	void ResolveCollision(PhysObject& other, CollisionPoints points);
	void ClearVelocity() { velocity = glm::vec3(0); }

private:
	glm::vec2 velocity, force;
	Transform& transform;
};

#endif

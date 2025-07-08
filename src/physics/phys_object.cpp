#include "phys_object.hpp"

PhysObject::PhysObject(Transform& parentTransform, float mass, glm::vec2 velocity)
	: Mass{mass}, velocity{velocity}, transform{&parentTransform} {}

// PhysObject& PhysObject::operator=(PhysObject&& other) {
// 	if (this != &other) {
// 		// Free the existing resource.
//
// 		// Copy the data pointer and its length from the
// 		// source object.
// 		transform = other.transform;
// 		Mass = other.Mass;
// 		velocity = other.velocity;
//
// 		// Release the data pointer from the source object so that
// 		// the destructor does not free the memory multiple times.
// 	}
// 	return *this;
// }

void PhysObject::ResolveForces(float dt) {
	velocity += (force / Mass) * dt;
	// 30 is added because the world space is so big (1920 x 1080) that if we are moving 9.81 pixels per second that is absolutely nothing
	// so we need to scale it up
	// TODO: think of a better way to do this??
	transform->Position += (velocity * dt) * 30.0f;
}

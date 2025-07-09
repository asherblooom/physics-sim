#include "phys_object.hpp"

PhysObject::PhysObject(Transform& parentTransform, float mass, glm::vec2 velocity)
	: Mass{mass}, velocity{velocity.x, -velocity.y}, transform{&parentTransform} {}

void PhysObject::ResolveForces(float dt) {
	velocity += (force / Mass) * dt;
	// 30 is added because the world space is so big (1920 x 1080) that if we are moving 9.81 pixels per second that is absolutely nothing
	// so we need to scale it up
	// TODO: think of a better way to do this??
	transform->Position += (velocity * dt) * 30.0f;
	if (transform->Position.x >= FLT_MAX) {
		transform->Position.x = FLT_MAX;
	}
	if (transform->Position.y >= FLT_MAX) {
		transform->Position.y = FLT_MAX;
	}
}

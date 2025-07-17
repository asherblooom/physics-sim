#include "phys_object.hpp"
#include <iostream>

PhysObject::PhysObject(Transform& parentTransform, float mass, glm::vec2 velocity)
	: InverseMass{1 / mass}, velocity{velocity.x, -velocity.y}, transform{parentTransform} {}

void PhysObject::AddForce(glm::vec2 force) {
	this->force.x += force.x;
	// down is +ve y, up is moving towards y=0 (so -ve y)
	this->force.y += -force.y;
}

void PhysObject::ResolveForces(float dt, glm::vec2 gravity, float dampingFactor) {
	if (Static) return;

	glm::vec2 acceleration = force * InverseMass;
	gravity.y = -gravity.y;
	if (HasGravity) acceleration += gravity;

	velocity += acceleration * dt;
	// 30 is used because the world space is so big (1920 x 1080) that if we are moving 9.81 pixels per second that is absolutely nothing
	// so we need to scale it up
	// TODO: think of a better way to do this??
	transform.Position += (velocity * dt) * 30.0f;

	// consistent amount of damping regardless of framerate
	float damping = powf(dampingFactor, dt);
	velocity *= damping;
	force = glm::vec2(0, 0);
}

void PhysObject::ResolveCollision(PhysObject& other, CollisionPoints points) {
	// TODO: static!
	if (other.Static) {
		this->transform.Position -= points.Normal * points.Depth;
	} else if (this->Static) {
		other.transform.Position += points.Normal * points.Depth;
	} else {
		float totalMass = this->InverseMass + other.InverseMass;
		this->transform.Position -= points.Normal * points.Depth * (this->InverseMass / totalMass);
		other.transform.Position += points.Normal * points.Depth * (other.InverseMass / totalMass);
	}
	// this->velocity = glm::vec2(0);
	// other.velocity = glm::vec2(0);
	// TODO: if position below bounds, fix it!!
}

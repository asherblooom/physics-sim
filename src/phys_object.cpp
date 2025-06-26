#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject(glm::vec2 center, glm::vec2 size, float mass, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: GameObject{center - size / 2.0f, size, texture, color}, Center(center), MassInv((mass == 0) ? 0 : (1 / mass)), velocity(velocity), force(glm::vec2(0, 0)) {}

void PhysObject::ResolveForces(float dt) {
	velocity += force * (MassInv * dt);
	Center += velocity * dt;
}

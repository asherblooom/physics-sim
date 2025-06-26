#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject(glm::vec2 center, glm::vec2 size, float mass, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: GameObject{center - size / 2.0f, size, texture, color}, Center(center), Mass(mass), velocity({velocity.x, -velocity.y}), force(glm::vec2(0, 0)) {}

void PhysObject::ResolveForces(float dt) {
	velocity += (force / Mass) * dt;
	// 30 is added because the world space is so big (1920 x 1080) that if we are moving 9.81 pixels per second that is absolutely nothing
	// so we need to scale it up
	// TODO: think of a better way to do this??
	Center += (velocity * dt) * 30.0f;
}

// position is top left corner of box containing object, used for rendering purposes
void PhysObject::SetRenderPosition(glm::vec2 position) {
	this->renderPosition = position;
	Center = position + RenderSize / 2.0f;
}
const glm::vec2& PhysObject::RenderPosition() {
	this->renderPosition = Center - RenderSize / 2.0f;
	return this->renderPosition;
}

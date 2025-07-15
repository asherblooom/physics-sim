#include "collision_volume.hpp"
#include <iostream>
#include "glm/detail/func_geometric.hpp"
CollisionPoints detectAABBCircleCollision(AABBVolume& aabb, CircleVolume& circle);

//------------constructors
CollisionVolume::CollisionVolume(VolumeType type, Transform& parentTransform)
	: Type{type},
	  PositionOffset{glm::vec2(0)},
	  RotationOffset{0},
	  SizeMultiplier{glm::vec2(1.0f)},
	  transform{parentTransform} {};
CircleVolume::CircleVolume(Transform& parentTransform)
	: CollisionVolume{CIRCLE, parentTransform} {}
AABBVolume::AABBVolume(Transform& parentTransform)
	: CollisionVolume{AABB, parentTransform} {}

//------------collision detection functions
CollisionPoints CircleVolume::DetectCircleCollision(CircleVolume& c) {
	float radii = this->getRadius() + c.getRadius();
	glm::vec2 delta = this->getCenter() - c.getCenter();
	float deltaLength = glm::length(delta);

	if (deltaLength < radii) {
		float depth = (radii - deltaLength);
		glm::vec2 normal = glm::normalize(delta);
		glm::vec2 localA = normal * this->getRadius();
		glm::vec2 localB = -normal * c.getRadius();

		return {localA, localB, normal, depth, true};
	}
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}
CollisionPoints AABBVolume::DetectAABBCollision(AABBVolume& c) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}
CollisionPoints CircleVolume::DetectAABBCollision(AABBVolume& c) {
	return detectAABBCircleCollision(c, *this);
}
CollisionPoints AABBVolume::DetectCircleCollision(CircleVolume& c) {
	return detectAABBCircleCollision(*this, c);
}
CollisionPoints detectAABBCircleCollision(AABBVolume& aabb, CircleVolume& circle) {
	glm::vec2 boxSize = aabb.getDimensions() / 2.0f;
	glm::vec2 centerDst = circle.getCenter() - aabb.getCenter();
	glm::vec2 clampDst = glm::clamp(centerDst, -boxSize, boxSize);
	glm::vec2 closestPoint = aabb.getCenter() + clampDst;
	// if this is 0, normal calculation does not work!
	glm::vec2 mycalc = closestPoint - circle.getCenter();
	float distance = glm::length(mycalc);

	if (distance < circle.getRadius()) {
		glm::vec2 collisionNormal;
		if (mycalc == glm::vec2(0))
			collisionNormal = glm::vec2(0, 1);
		else
			collisionNormal = glm::normalize(mycalc);
		float depth = (circle.getRadius() - distance);

		glm::vec2 localA = glm::vec2();
		glm::vec2 localB = -collisionNormal * circle.getRadius();

		return {localA, localB, collisionNormal, depth, true};
	}
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

//------------mouse detection functions
bool CircleVolume::DetectMouseOver(glm::vec2 mousePos) {
	auto distance = glm::length(mousePos - this->getCenter());
	if (distance <= this->getRadius())
		return true;
	else
		return false;
}
bool AABBVolume::DetectMouseOver(glm::vec2 mousePos) {
	return false;
}

//------------helper functions
float CircleVolume::getRadius() {
	float renderRadius = transform.Size.x >= transform.Size.y ? transform.Size.x / 2.0f : transform.Size.y / 2.0f;
	float multipliedRadius = SizeMultiplier.x >= SizeMultiplier.y ? renderRadius * SizeMultiplier.x : renderRadius * SizeMultiplier.y;
	return multipliedRadius;
}
glm::vec2 CircleVolume::getCenter() {
	return transform.Position + PositionOffset + transform.Size / 2.0f;
}
glm::vec2 AABBVolume::getDimensions() {
	return transform.Size * SizeMultiplier;
}
glm::vec2 AABBVolume::getCenter() {
	return transform.Position + PositionOffset + transform.Size / 2.0f;
}

#include "collision_volume.hpp"
CollisionPoints detectAABBCircleCollision(AABBVolume& aabb, CircleVolume& circle);

//constructors
CollisionVolume::CollisionVolume(VolumeType type, Transform& parentTransform)
	: Type{type},
	  PositionOffset{glm::vec2(0)},
	  RotationOffset{0},
	  SizeMultiplier{glm::vec2(1)},
	  transform{parentTransform} {};
CircleVolume::CircleVolume(Transform& parentTransform)
	: CollisionVolume{CIRCLE, parentTransform} {}
AABBVolume::AABBVolume(Transform& parentTransform)
	: CollisionVolume{AABB, parentTransform} {}

CollisionPoints CircleVolume::DetectCircleCollision(CircleVolume& c) {
	float radii = this->getRadius() + c.getRadius();
	glm::vec2 delta = c.getCenter() - this->getCenter();
	float deltaLength = glm::length(delta);

	if (deltaLength < radii) {
		float penetration = (radii - deltaLength);
		glm::vec2 normal = glm::normalize(delta);
		glm::vec2 localA = normal * this->getRadius();
		glm::vec2 localB = -normal * c.getRadius();

		return {localA, localB, normal, penetration, true};
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

float CircleVolume::getRadius() {
	float radius = transform.Size.x >= transform.Size.y ? transform.Size.x / 2 : transform.Size.y / 2;
	float multipliedRadius = SizeMultiplier.x >= SizeMultiplier.y ? radius * SizeMultiplier.x : radius * SizeMultiplier.y;
	return multipliedRadius;
}
glm::vec2 CircleVolume::getCenter() {
	return transform.Position + PositionOffset + getRadius();
}
glm::vec2 AABBVolume::getCenter() {
	return transform.Position + PositionOffset + (transform.Size * SizeMultiplier);
}

CollisionPoints detectAABBCircleCollision(AABBVolume& aabb, CircleVolume& circle) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

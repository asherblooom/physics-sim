#include "collision_volume.hpp"
CollisionPoints detectPlaneCircleCollision(PlaneVolume& plane, CircleVolume& circle);

CollisionPoints CircleVolume::DetectCircleCollision(CircleVolume& c) {
	float radii = this->Radius + c.Radius;
	glm::vec2 delta = c.Center - this->Center;
	float deltaLength = glm::length(delta);

	if (deltaLength < radii) {
		float penetration = (radii - deltaLength);
		glm::vec2 normal = glm::normalize(delta);
		glm::vec2 localA = normal * this->Radius;
		glm::vec2 localB = -normal * c.Radius;

		return {localA, localB, normal, penetration, true};
	}
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}
CollisionPoints PlaneVolume::DetectPlaneCollision(PlaneVolume& c) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

CollisionPoints CircleVolume::DetectPlaneCollision(PlaneVolume& c) {
	return detectPlaneCircleCollision(c, *this);
}
CollisionPoints PlaneVolume::DetectCircleCollision(CircleVolume& c) {
	return detectPlaneCircleCollision(*this, c);
}

bool CircleVolume::DetectMouseOver(glm::vec2 mousePos) {
	auto distance = glm::length(mousePos - this->Center);
	if (distance <= this->Radius)
		return true;
	else
		return false;
}
bool PlaneVolume::DetectMouseOver(glm::vec2 mousePos) {
	return false;
}

CollisionPoints detectPlaneCircleCollision(PlaneVolume& plane, CircleVolume& circle) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

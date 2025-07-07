#include <glm/glm.hpp>
#include <iostream>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/resource_manager.hpp>

Ball::Ball(glm::vec2 center, float diameter, float mass, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{center,
				 glm::vec2(diameter),
				 mass,
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity},
	  Radius{diameter / 2.0f} {}

CollisionPoints Ball::CollideWithBall(Ball &b) {
	float radii = this->Radius + b.Radius;
	glm::vec2 delta = b.Center - this->Center;
	float deltaLength = glm::length(delta);

	if (deltaLength < radii) {
		float penetration = (radii - deltaLength);
		glm::vec2 normal = glm::normalize(delta);
		glm::vec2 localA = normal * this->Radius;
		glm::vec2 localB = -normal * b.Radius;

		return {localA, localB, normal, penetration, true};
	}
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

CollisionPoints Ball::CollideWithPlane(Plane &p) {
	return {glm::vec2(0), glm::vec2(0), glm::vec2(0), 0, false};
}

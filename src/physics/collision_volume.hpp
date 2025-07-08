#ifndef COLLIDERS_HPP
#define COLLIDERS_HPP

#include <glm/glm.hpp>
#include "../transform.hpp"

class CircleVolume;
class PlaneVolume;

enum VolumeType {
	SPHERE,
	PLANE
};

class CollisionVolume {
public:
	VolumeType Type;

	// collision functions using visitor pattern/double dispatch
	virtual CollisionPoints DetectCollision(CollisionVolume& c) = 0;
	virtual CollisionPoints DetectCircleCollision(CircleVolume& c) = 0;
	virtual CollisionPoints DetectPlaneCollision(PlaneVolume& c) = 0;

	virtual bool DetectMouseOver(glm::vec2 mousePos) = 0;
};

class CircleVolume : CollisionVolume {
public:
	glm::vec2 Center;
	float Radius;

	CollisionPoints DetectCollision(CollisionVolume& c) override {
		return c.DetectCircleCollision(*this);
	}
	CollisionPoints DetectCircleCollision(CircleVolume& c) override;
	CollisionPoints DetectPlaneCollision(PlaneVolume& c) override;

	bool DetectMouseOver(glm::vec2 mousePos) override;
};

class PlaneVolume : CollisionVolume {
public:
	glm::vec2 Normal;
	float Distance;

	CollisionPoints DetectCollision(CollisionVolume& c) override {
		return c.DetectPlaneCollision(*this);
	}
	CollisionPoints DetectCircleCollision(CircleVolume& c) override;
	CollisionPoints DetectPlaneCollision(PlaneVolume& c) override;

	bool DetectMouseOver(glm::vec2 mousePos) override;
};

#endif

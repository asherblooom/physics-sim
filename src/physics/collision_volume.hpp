#ifndef COLLIDERS_HPP
#define COLLIDERS_HPP

#include <glm/glm.hpp>
#include "../transform.hpp"

class CircleVolume;
class AABBVolume;

enum VolumeType {
	CIRCLE,
	AABB
};

class CollisionVolume {
public:
	VolumeType Type;
	// options for editing the volume independently of the (rendered) sprite
	glm::vec2 PositionOffset;
	float RotationOffset;
	glm::vec2 SizeMultiplier;

	// collision functions using visitor pattern/double dispatch
	virtual CollisionPoints DetectCollision(CollisionVolume& c) = 0;
	virtual CollisionPoints DetectCircleCollision(CircleVolume& c) = 0;
	virtual CollisionPoints DetectAABBCollision(AABBVolume& c) = 0;

	virtual bool DetectMouseOver(glm::vec2 mousePos) = 0;

protected:
	Transform* transform;
	CollisionVolume(VolumeType type, Transform& parentTransform);
	virtual glm::vec2 getCenter() = 0;
};

class CircleVolume : public CollisionVolume {
public:
	CircleVolume(Transform& parentTransform);

	CollisionPoints DetectCollision(CollisionVolume& c) override {
		return c.DetectCircleCollision(*this);
	}
	CollisionPoints DetectCircleCollision(CircleVolume& c) override;
	CollisionPoints DetectAABBCollision(AABBVolume& c) override;

	bool DetectMouseOver(glm::vec2 mousePos) override;

private:
	float getRadius();
	glm::vec2 getCenter() override;
};

class AABBVolume : public CollisionVolume {
public:
	AABBVolume(Transform& parentTransform);

	CollisionPoints DetectCollision(CollisionVolume& c) override {
		return c.DetectAABBCollision(*this);
	}
	CollisionPoints DetectCircleCollision(CircleVolume& c) override;
	CollisionPoints DetectAABBCollision(AABBVolume& c) override;

	bool DetectMouseOver(glm::vec2 mousePos) override;

private:
	glm::vec2 getCenter() override;
};

#endif

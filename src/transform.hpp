#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

struct CollisionPoints {
	glm::vec2 A;	   // Furthest point of A into B
	glm::vec2 B;	   // Furthest point of B into A
	glm::vec2 Normal;  // B – A normalized
	float Depth;	   // Length of B – A
	bool HasCollision;
};

struct Transform {	// Describes an objects location
	glm::vec2 Position;
	glm::vec2 Size;
	float Rotation;
};

#endif

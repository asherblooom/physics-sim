#ifndef PLANE_HPP
#define PLANE_HPP

#include <glm/glm.hpp>

#include <physics-sim/phys_object.hpp>

// a plane object
class Plane : public PhysObject {
public:
	const glm::vec2 Normal;
	float Distance = 0;	 //??
	float Length;
	Plane(glm::vec2 center, glm::vec2 normal, float length, glm::vec3 color = glm::vec3(1.0f));

private:
};

#endif

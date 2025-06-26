#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

#include <physics-sim/phys_object.hpp>

// a ball object
class Ball : public PhysObject {
public:
	const float Radius;
	Ball(glm::vec2 center, float diameter = 1.0f, float mass = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

private:
};

#endif

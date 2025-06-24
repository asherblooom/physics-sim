#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

#include <physics-sim/phys_object.hpp>

// a ball object
class Ball : public PhysObject {
public:
	Ball(glm::vec2 pos, float diameter = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
	const float Radius;
};

#endif

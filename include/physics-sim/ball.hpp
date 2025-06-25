#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

#include <physics-sim/phys_object.hpp>

// a ball object
class Ball : public PhysObject {
public:
	Ball(glm::vec2 center, float diameter = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));
	const float Radius;
	const glm::vec2& Center() const { return center; }
	// position must be updated every time center is updated, and vice versa
	void SetCenter(glm::vec2 center);
	void SetPosition(glm::vec2 position) override;

private:
	glm::vec2 center;
};

#endif

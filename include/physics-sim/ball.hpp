#ifndef BALL_HPP
#define BALL_HPP

#include <glm/glm.hpp>

#include <physics-sim/phys_object.hpp>

// a ball object
class Ball : public PhysObject {
public:
	glm::vec2 Center;
	const float Radius;
	Ball(glm::vec2 center, float diameter = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

	// need to calculate position from center when getting and vice versa when setting
	// done this way as position (used for rendering) will most likely be queried far less than center (used for physics)
	void SetPosition(glm::vec2 position) override;
	const glm::vec2& Position() override;

private:
};

#endif

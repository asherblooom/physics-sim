#include <physics-sim/ball.hpp>
#include <physics-sim/resource_manager.hpp>

#include <cmath>

Ball::Ball(glm::vec2 center, float diameter, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{center - (diameter * 50) / 2,
				 diameter * glm::vec2(50),
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity},
	  Radius{diameter / 2.0f},
	  center{center} {}

// position is top left corner of box containing ball, for rendering purposes
void Ball::SetCenter(glm::vec2 center) {
	this->center = center;
	position = center - Size / 2.0f;
}
void Ball::SetPosition(glm::vec2 position) {
	this->position = position;
	center = position + Size / 2.0f;
}

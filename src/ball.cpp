#include <physics-sim/ball.hpp>
#include <physics-sim/resource_manager.hpp>

#include <cmath>

Ball::Ball(glm::vec2 center, float diameter, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{center - (diameter * 50) / 2,
				 diameter * glm::vec2(50),
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity},
	  Center{center},
	  Radius{diameter / 2.0f} {}

// position is top left corner of box containing ball, used for rendering purposes
void Ball::SetPosition(glm::vec2 position) {
	this->position = position;
	Center = position + Size / 2.0f;
}
const glm::vec2& Ball::Position() {
	this->position = Center - Size / 2.0f;
	return this->position;
}

#include <physics-sim/ball.hpp>
#include <physics-sim/resource_manager.hpp>

#include <cmath>

Ball::Ball(glm::vec2 center, float diameter, float mass, glm::vec3 color, glm::vec2 velocity)
	: PhysObject{center,
				 diameter * glm::vec2(50),
				 mass,
				 ResourceManager::GetTexture("ball"),
				 color,
				 velocity},
	  Radius{diameter / 2.0f} {}

// position is top left corner of box containing ball, used for rendering purposes
void Ball::SetRenderPosition(glm::vec2 position) {
	this->renderPosition = position;
	Center = position + RenderSize / 2.0f;
}
const glm::vec2& Ball::RenderPosition() {
	this->renderPosition = Center - RenderSize / 2.0f;
	return this->renderPosition;
}

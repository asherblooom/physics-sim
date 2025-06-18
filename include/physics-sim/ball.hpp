#ifndef BALL_HPP
#define BALL_HPP

#include <physics-sim/phys_object.hpp>

class Ball : public PhysObject {
public:
	Ball();
	Ball(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity);
};

#endif

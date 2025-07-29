
#ifndef CIRCLE_RENDERER_HPP
#define CIRCLE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render_object.hpp"

class CircleRenderer {
public:
	CircleRenderer();
	~CircleRenderer();
	// Renders a defined quad textured with given sprite
	void DrawCircle(RenderObject& object);

private:
	int numSegments = 32;
	unsigned int VAO;
	// Initializes and configures VAO
	void initRenderData();
};

#endif

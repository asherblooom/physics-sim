
#ifndef CIRCLE_RENDERER_HPP
#define CIRCLE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render_object.hpp"
#include "renderer.hpp"
#include "shader.hpp"

class CircleRenderer : public Renderer {
public:
	CircleRenderer(Shader shader, unsigned int segments = 32);
	~CircleRenderer();
	// Renders a defined quad textured with given sprite
	void Draw(RenderObject& object) override;

private:
	unsigned int numSegments;
	// Initializes and configures VAO
	void initVertices() override;
};

#endif

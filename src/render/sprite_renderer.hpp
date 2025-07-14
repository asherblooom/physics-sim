
#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render_object.hpp"

class SpriteRenderer {
public:
	SpriteRenderer();
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(RenderObject& object);

private:
	// Render state
	unsigned int quadVAO;
	// Initializes and configures quadVAO
	void initRenderData();
};

#endif

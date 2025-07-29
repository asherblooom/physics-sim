
#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render_object.hpp"
#include "renderer.hpp"
#include "shader.hpp"

class SpriteRenderer : public Renderer {
public:
	SpriteRenderer(Shader shader);
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void Draw(RenderObject& object) override;

private:
	// Initializes and configures VAO
	void initVertices() override;
};

#endif

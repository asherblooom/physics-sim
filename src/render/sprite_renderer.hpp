
#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer {
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);

private:
	// Render state
	Shader& shader;
	unsigned int quadVAO;
	// Initializes and configures quadVAO
	void initRenderData();
};

#endif

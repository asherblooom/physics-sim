#include "sprite_renderer.hpp"
#include <vector>

SpriteRenderer::SpriteRenderer(Shader shader) : Renderer(shader) {
	initVertices();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::Draw(RenderObject& object) {
	shader.Use();
	setModelMatrix(object.transform());
	shader.SetVector3f("spriteColor", object.Color);

	glActiveTexture(GL_TEXTURE0);
	object.Texture.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initVertices() {
	std::vector<Vertex> vertices = {
		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f},

		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f, 0.0f}};

	initVAO(vertices);
}

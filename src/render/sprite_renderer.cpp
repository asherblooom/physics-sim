#include "sprite_renderer.hpp"

SpriteRenderer::SpriteRenderer() {
	initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &quadVAO);
}

void SpriteRenderer::DrawSprite(RenderObject& object) {
	const Transform& transform = object.transform();
	// prepare transformations
	object.shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	// first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
	model = glm::translate(model, glm::vec3(transform.Position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * transform.Size.x, 0.5f * transform.Size.y, 0.0f));	 // move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(transform.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));			 // then rotate
	model = glm::translate(model, glm::vec3(-0.5f * transform.Size.x, -0.5f * transform.Size.y, 0.0f));	 // move origin back

	model = glm::scale(model, glm::vec3(transform.Size, 1.0f));	 // last scale

	object.shader.SetMatrix4("model", model);

	// render textured quad
	object.shader.SetVector3f("spriteColor", object.Color);

	glActiveTexture(GL_TEXTURE0);
	object.Texture.Bind();

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// format: pos x, pos y, tex x, tex y
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}

#include "sprite_renderer.hpp"

struct vertex {
	// Position
	float x;
	float y;
	// Texture coordinates
	float s;
	float t;
};

SpriteRenderer::SpriteRenderer() {
	initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &VAO);
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

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void DrawCircle(float cx, float cy, float r, int num_segments, vertex vertices[]) {
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);	//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;  //we start at angle = 0
	float y = 0;

	for (int i = 0; i < num_segments; i++) {
		vertices[i] = {x + cx, y + cy, 0, 0};

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
}

void SpriteRenderer::initRenderData() {
	// configure VAO/VBO
	unsigned int VBO;

	vertex vertices[16];
	DrawCircle(0.5, 0.5, 0.5, 16, vertices);

	// initialise VBO buffer and fill it with data from vertices
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// transfer data from VBO buffer to VAO indices 0 and 1
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, s));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}

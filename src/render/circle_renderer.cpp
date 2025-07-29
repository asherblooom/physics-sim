#include "circle_renderer.hpp"
#include <iostream>
#include <vector>

struct vertex {
	// Position
	float x;
	float y;
	// Texture coordinates
	float s;
	float t;
};

CircleRenderer::CircleRenderer() {
	initRenderData();
}

CircleRenderer::~CircleRenderer() {
	glDeleteVertexArrays(1, &VAO);
}

void CircleRenderer::DrawCircle(RenderObject& object) {
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
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);
	glBindVertexArray(0);
}

void genPoints(float cx, float cy, float r, int num_segments, std::vector<vertex>& vertices) {
	vertices.emplace_back(cx, cy, 0, 0);
	for (int i = 0; i < num_segments + 1; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);  //get the current angle

		float x = r * cosf(theta);	//calculate the x component
		float y = r * sinf(theta);	//calculate the y component

		vertices.emplace_back(x + cx, y + cy, 0, 0);  //output vertex 	// y = s * t + c * y;
	}
}

void CircleRenderer::initRenderData() {
	// configure VAO/VBO
	unsigned int VBO;

	std::vector<vertex> vertices;
	genPoints(0.5, 0.5, 0.5, numSegments, vertices);

	// initialise VBO buffer and fill it with data from vertices
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

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

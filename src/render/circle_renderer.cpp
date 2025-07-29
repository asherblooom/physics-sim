#include "circle_renderer.hpp"
#include <vector>

CircleRenderer::CircleRenderer(Shader shader, unsigned int segments) : Renderer(shader), numSegments(segments) {
	initVertices();
}

CircleRenderer::~CircleRenderer() {
	glDeleteVertexArrays(1, &VAO);
}

void CircleRenderer::Draw(RenderObject& object) {
	shader.Use();
	setModelMatrix(object.transform());
	shader.SetVector3f("spriteColor", object.Color);

	glActiveTexture(GL_TEXTURE0);
	object.Texture.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);
	glBindVertexArray(0);
}

void CircleRenderer::initVertices() {
	std::vector<Vertex> vertices;
	float cx = 0.5, cy = 0.5, r = 0.5;

	vertices.emplace_back(cx, cy, 0, 0);
	for (unsigned int i = 0; i < numSegments + 1; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);  //get the current angle

		float x = r * cosf(theta);	//calculate the x component
		float y = r * sinf(theta);	//calculate the y component

		vertices.emplace_back(x + cx, y + cy, 0, 0);  //output vertex 	// y = s * t + c * y;
	}

	initVAO(vertices);
}

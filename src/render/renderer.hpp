#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "render_object.hpp"
#include "shader.hpp"

struct Vertex {
	// Position
	float x;
	float y;
	// Texture coordinates
	float s;
	float t;
};

class Renderer {
public:
	virtual void Draw(RenderObject& object) = 0;

protected:
	unsigned int VAO;
	Shader shader;
	void initVAO(std::vector<Vertex> vertices) {
		// initialise VBO buffer and fill it with data from vertices
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		// transfer data from VBO buffer to VAO indices 0 and 1
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, s));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &VBO);
	};
	virtual void initVertices() = 0;

	void setModelMatrix(Transform transform) {
		shader.Use();
		glm::mat4 model = glm::mat4(1.0f);
		// first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
		model = glm::translate(model, glm::vec3(transform.Position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * transform.Size.x, 0.5f * transform.Size.y, 0.0f));	 // move origin of rotation to center of quad
		model = glm::rotate(model, glm::radians(transform.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));			 // then rotate
		model = glm::translate(model, glm::vec3(-0.5f * transform.Size.x, -0.5f * transform.Size.y, 0.0f));	 // move origin back

		model = glm::scale(model, glm::vec3(transform.Size, 1.0f));	 // last scale

		shader.SetMatrix4("model", model);
	};

	Renderer(Shader shader) : shader{shader} {};
	virtual ~Renderer() {};
};

#endif

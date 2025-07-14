#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include <glm/glm.hpp>

#include "../transform.hpp"
#include "shader.hpp"
#include "texture.hpp"

// holds properties used for rendering objects
class RenderObject {
public:
	glm::vec3 Color;
	Shader shader;
	Texture2D Texture;
	const Transform& transform() const { return _transform; }

	RenderObject(Transform& parentTransform, Texture2D texture, Shader shader, glm::vec3 color);

private:
	Transform& _transform;
};

#endif

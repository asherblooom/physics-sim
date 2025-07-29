#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include <glm/glm.hpp>

#include "../transform.hpp"
#include "texture.hpp"

// holds properties used for rendering objects
class RenderObject {
public:
	glm::vec3 Color;
	Texture2D Texture;
	const Transform& transform() const { return _transform; }

	RenderObject(Transform& parentTransform, Texture2D texture, glm::vec3 color);

private:
	Transform& _transform;
};

#endif

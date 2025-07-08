#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP

#include <glm/glm.hpp>

#include "../transform.hpp"
#include "sprite_renderer.hpp"
#include "texture.hpp"

// holds properties used for rendering objects
class RenderObject {
public:
	glm::vec3 Color;

	void Draw();
	RenderObject(Transform& parentTransform, SpriteRenderer& renderer, Texture2D texture, glm::vec3 color);

private:
	Transform* transform;
	SpriteRenderer* renderer;
	Texture2D texture;
};

#endif

#include "render_object.hpp"

RenderObject::RenderObject(Transform& parentTransform, Texture2D texture, glm::vec3 color)
	: Color{color}, Texture{texture}, _transform{parentTransform} {}

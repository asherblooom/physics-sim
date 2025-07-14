#include "render_object.hpp"

RenderObject::RenderObject(Transform& parentTransform, Texture2D texture, Shader shader, glm::vec3 color)
	: Color{color}, shader{shader}, Texture{texture}, _transform{parentTransform} {}

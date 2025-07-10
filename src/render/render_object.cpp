#include "render_object.hpp"
#include <iostream>

RenderObject::RenderObject(Transform& parentTransform, Texture2D texture, glm::vec3 color)
	: Color{color}, transform{parentTransform}, texture{texture} {}

void RenderObject::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(texture, transform.Position, transform.Size, transform.Rotation, Color);
}

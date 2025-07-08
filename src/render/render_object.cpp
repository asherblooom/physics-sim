#include "render_object.hpp"

RenderObject::RenderObject(Transform& parentTransform, SpriteRenderer& renderer, Texture2D texture, glm::vec3 color)
	: Color{color}, transform{&parentTransform}, renderer{&renderer}, texture{texture} {}

void RenderObject::Draw() {
	renderer->DrawSprite(texture, transform->Position, transform->Size, transform->Rotation, Color);
}

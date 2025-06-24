#include <physics-sim/phys_object.hpp>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color)
	: Color{color}, Size{size}, Texture{texture}, position{pos}, rotation{0.0f} {}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Texture, this->position, this->Size, this->rotation, this->Color);
}

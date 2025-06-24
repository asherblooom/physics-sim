#include <physics-sim/phys_object.hpp>

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color)
	: Color{color}, position{pos}, size{size}, texture{texture}, rotation{0.0f} {}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->texture, this->position, this->size, this->rotation, this->Color);
}

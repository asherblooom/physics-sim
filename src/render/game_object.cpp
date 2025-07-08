#include "game_object.hpp"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color)
	: RenderColor{color}, RenderSize{size}, RenderTexture{texture}, renderPosition{pos}, rotation{0.0f} {}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->RenderTexture, this->RenderPosition(), this->RenderSize, this->rotation, this->RenderColor);
}

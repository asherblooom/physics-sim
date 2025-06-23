#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: Color(color), position(pos), size(size), velocity(velocity), force(glm::vec2(0, 0)), rotation(0.0f), destroyed(false), texture(texture) {}

void PhysObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->texture, this->position, this->size, this->rotation, this->Color);
}

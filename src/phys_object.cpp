#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Destroyed(false), Texture(texture) {}

void PhysObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

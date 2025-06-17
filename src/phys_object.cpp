#include <physics-sim/phys_object.hpp>

PhysObject::PhysObject()
	: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {}

PhysObject::PhysObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) {}

void PhysObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

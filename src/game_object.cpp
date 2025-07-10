#include "game_object.hpp"
#include "physics/collision_volume.hpp"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, VolumeType volume, Texture2D texture, float mass, glm::vec2 velocity, glm::vec3 color)
	: transform{std::make_unique<Transform>(position, size, 0)},
	  Render{std::make_unique<RenderObject>(*transform, texture, color)},
	  Physics{std::make_unique<PhysObject>(*transform, mass, velocity)} {
	if (volume == CIRCLE) {
		BoundingVolume = std::make_unique<CircleVolume>(*transform);
	} else if (volume == AABB) {
		BoundingVolume = std::make_unique<AABBVolume>(*transform);
	}
}

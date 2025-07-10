#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <memory>

#include "physics/collision_volume.hpp"
#include "physics/phys_object.hpp"
#include "render/render_object.hpp"
#include "transform.hpp"

class GameObject {
public:
	GameObject(glm::vec2 position,
			   glm::vec2 size,
			   VolumeType volume,
			   Texture2D texture,
			   float mass = 1.0f,
			   glm::vec2 velocity = glm::vec2(0),
			   glm::vec3 color = glm::vec3(1));

	std::unique_ptr<Transform> transform;
	std::unique_ptr<RenderObject> Render;
	std::unique_ptr<PhysObject> Physics;
	std::unique_ptr<CollisionVolume> BoundingVolume;
};

#endif

#include <physics-sim/object_manager.hpp>

std::vector<std::shared_ptr<PhysObject>> ObjectManager::Objects;

void ObjectManager::renderObjects(SpriteRenderer& renderer) {
	for (auto object : Objects) {
		object->Draw(renderer);
	}
}

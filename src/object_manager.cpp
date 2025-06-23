//TODO: DELETE THIS??????
#include <physics-sim/object_manager.hpp>

std::vector<std::unique_ptr<PhysObject>> ObjectManager::Objects;

void ObjectManager::RenderObjects(SpriteRenderer& renderer) {
	for (auto& object : Objects) {
		object->Draw(renderer);
	}
}

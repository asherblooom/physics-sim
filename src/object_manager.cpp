#include <physics-sim/object_manager.hpp>
std::map<std::string, std::shared_ptr<PhysObject>> ObjectManager::Objects;

void ObjectManager::deleteObject(std::string name) {
	Objects.erase(name);
}
std::shared_ptr<PhysObject> ObjectManager::getObject(std::string name) {
	return Objects[name];
}
void ObjectManager::renderObjects(SpriteRenderer& renderer) {
	for (auto object : Objects) {
		object.second->Draw(renderer);
	}
}

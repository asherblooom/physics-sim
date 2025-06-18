#include <physics-sim/object_manager.hpp>
std::map<std::string, std::shared_ptr<PhysObject>> ObjectManager::Objects;

template <typename Obj>
	requires std::is_base_of_v<PhysObject, Obj>
std::shared_ptr<PhysObject> ObjectManager::addObject(std::string name, glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
	std::shared_ptr<PhysObject> object = std::make_shared<Obj>(pos, color, velocity);
	Objects[name] = object;
	return object;
}
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

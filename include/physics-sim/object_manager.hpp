#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP
#include <map>
#include <memory>
#include <physics-sim/ball.hpp>
#include <physics-sim/phys_object.hpp>
#include <string>
#include "physics-sim/sprite_renderer.hpp"

class ObjectManager {
private:
	static std::map<std::string, std::shared_ptr<PhysObject>> Objects;
	// singleton class
	ObjectManager() {}

public:
	template <typename Obj>
		requires std::is_base_of_v<PhysObject, Obj>
	static std::shared_ptr<PhysObject> addObject(std::string name, glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
		std::shared_ptr<PhysObject> object = std::make_shared<Obj>(pos, color, velocity);
		Objects[name] = object;
		return object;
	}
	static void deleteObject(std::string name) {
		Objects.erase(name);
	}
	static std::shared_ptr<PhysObject> getObject(std::string name) {
		return Objects[name];
	}
	static void renderObjects(SpriteRenderer& renderer) {
		for (auto object : Objects) {
			object.second->Draw(renderer);
		}
	}
};

#endif

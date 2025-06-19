#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP
#include <glm/glm.hpp>
#include <memory>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/sprite_renderer.hpp>
#include <string>
#include <vector>

class ObjectManager {
private:
	static std::vector<std::shared_ptr<PhysObject>> Objects;
	// singleton class
	ObjectManager() {}

public:
	//TODO: is it possible to get this in the cpp file? I'm not sure...
	template <typename Obj>
		requires std::is_base_of_v<PhysObject, Obj>
	static std::shared_ptr<PhysObject> addObject(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
		std::shared_ptr<PhysObject> object = std::make_shared<Obj>(pos, color, velocity);
		Objects.push_back(object);
		return object;
	}

	static void deleteObject(int index) {
		Objects.erase(Objects.begin() + index);
	}

	static std::vector<std::shared_ptr<PhysObject>> getObjects() {
		return Objects;
	}

	static void renderObjects(SpriteRenderer& renderer);
};

#endif

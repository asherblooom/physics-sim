#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/sprite_renderer.hpp>
#include <string>

class ObjectManager {
private:
	static std::map<std::string, std::shared_ptr<PhysObject>> Objects;
	// singleton class
	ObjectManager() {}

public:
	//TODO: is it possible to get this in the cpp file? I'm not sure...
	template <typename Obj>
		requires std::is_base_of_v<PhysObject, Obj>
	static std::shared_ptr<PhysObject> addObject(std::string name, glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
		std::shared_ptr<PhysObject> object = std::make_shared<Obj>(pos, color, velocity);
		Objects[name] = object;
		return object;
	}

	static void deleteObject(std::string name);

	static std::shared_ptr<PhysObject> getObject(std::string name);

	static void renderObjects(SpriteRenderer& renderer);
};

#endif

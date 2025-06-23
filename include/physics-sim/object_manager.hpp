//TODO: DELETE THIS??????
#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP
#include <glm/glm.hpp>
#include <memory>
#include <physics-sim/phys_object.hpp>
#include <physics-sim/sprite_renderer.hpp>
#include <vector>

class ObjectManager {
private:
	static std::vector<std::unique_ptr<PhysObject>> Objects;
	// singleton class
	ObjectManager() {}

public:
	template <typename Obj>
		requires std::is_base_of_v<PhysObject, Obj>
	static const PhysObject& AddObject(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
		std::unique_ptr<PhysObject> obj = std::make_unique<Obj>(pos, color, velocity);
		Objects.push_back(std::move(obj));
		return *Objects.back();
	}

	static void DeleteObject(int index) { Objects.erase(Objects.begin() + index); }

	static const std::vector<std::unique_ptr<PhysObject>>& GetObjects() { return Objects; }

	// renders all objects in Objects vector, using the provided renderer
	static void RenderObjects(SpriteRenderer& renderer);
};

#endif

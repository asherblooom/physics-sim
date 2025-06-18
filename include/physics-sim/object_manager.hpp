#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP
#include <map>
#include <physics-sim/phys_object.hpp>
#include <string>

class ObjectManager {
private:
	std::map<std::string, PhysObject> Objects;
	// singleton class
	ObjectManager() {}

public:
	template <typename Obj>
		requires std::derived_from<Obj, PhysObject>
	Obj addObject() {
	}
};

#endif

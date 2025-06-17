
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include <physics-sim/shader.hpp>

// A static singleton ResourceManager class that hosts several functions to load Shaders.
// Each loaded shader is also stored for future reference by string handles.
// All functions and resources are static and no public constructor is defined.
class ResourceManager {
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	// loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
	// If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(std::string name, const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	// retrieves a stored sader
	static Shader GetShader(std::string name);
	// properly de-allocates all loaded resources
	// TODO: use a destructor for this instead??
	static void Clear();

private:
	// private constructor, that is we do not want any actual resource manager objects.
	// Its members and functions should be publicly available (static).
	ResourceManager() {}
};

#endif

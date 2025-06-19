
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include <physics-sim/shader.hpp>
#include <physics-sim/texture.hpp>

// A static singleton ResourceManager class that hosts several functions to load Textures and Shaders.
// Each loaded texture and/or shader is also stored for future reference by string handles.
// All functions and resources are static and no public constructor is defined.
class ResourceManager {
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	// loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code.
	// If gShaderFile is not nullptr, it also loads a geometry shader
	static const Shader &LoadShader(std::string name, const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	// retrieves a stored sader
	static const Shader &GetShader(std::string name);
	// loads (and generates) a texture from file
	static const Texture2D &LoadTexture(std::string name, const char *file);
	// retrieves a stored texture
	static const Texture2D &GetTexture(std::string name);
	// properly de-allocates all loaded resources
	static void Clear();

private:
	// private constructor, that is we do not want any actual resource manager objects.
	// Its members and functions should be publicly available (static).
	ResourceManager() {}
};

#endif

#include <physics-sim/resource_manager.hpp>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

// Instantiate static variables
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}

Shader ResourceManager::LoadShader(std::string name, const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try {
		// open files
		std::ifstream vertexShaderFile{vShaderFile};
		std::ifstream fragmentShaderFile{fShaderFile};
		if (!vertexShaderFile)
			std::cout << "no vertex shader" << std::endl;
		if (!fragmentShaderFile)
			std::cout << "no fragment shader" << std::endl;

		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			if (!geometryShaderFile)
				std::cout << "no geometry shader" << std::endl;
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	} catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	const char *gShaderCode = geometryCode.c_str();
	// 2. now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	Shaders[name] = shader;
	return shader;
}

//TODO: include alpha???
Texture2D ResourceManager::LoadTexture(std::string name, const char *file, bool alpha) {
	unsigned char *header;

	unsigned int width;
	unsigned int height;
	unsigned int mipMapCount;

	unsigned int blockSize;
	unsigned int format;

	unsigned char *buffer = 0;

	// open the DDS file for binary reading and get file size
	std::FILE *f;
	if ((f = std::fopen(file, "rb")) == 0) {
		std::cout << "ERROR: incorrect file name\n";
		return Texture2D();
	}
	std::fseek(f, 0, SEEK_END);
	long file_size = ftell(f);
	std::fseek(f, 0, SEEK_SET);

	// allocate new unsigned char space with 4 (file code) + 124 (header size) bytes
	header = new unsigned char[128];
	// read in 128 bytes from the file
	std::fread(header, 1, 128, f);

	// compare the `DDS ` signature
	if (std::memcmp(header, "DDS ", 4) != 0) {
		std::cout << "ERROR: incorrect DDS signature\n";
		delete[] (buffer);
		delete[] (header);
		fclose(f);
		return Texture2D();
	}

	// extract height, width, and amount of mipmaps - yes it is stored height then width
	height = (header[12]) | (header[13] << 8) | (header[14] << 16) | (header[15] << 24);
	width = (header[16]) | (header[17] << 8) | (header[18] << 16) | (header[19] << 24);
	mipMapCount = (header[28]) | (header[29] << 8) | (header[30] << 16) | (header[31] << 24);

	// figure out what format to use for what fourCC file type it is
	// block size is about physical chunk storage of compressed data in file (important)
	if (header[84] == 'D') {
		switch (header[87]) {
			case '1':  // DXT1
				format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				blockSize = 8;
				break;
			case '3':  // DXT3
				format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				blockSize = 16;
				break;
			case '5':  // DXT5
				format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				blockSize = 16;
				break;
			case '0':  // DX10
					   // unsupported, else will error
					   // as it adds sizeof(struct DDS_HEADER_DXT10) between pixels
					   // so, buffer = malloc((file_size - 128) - sizeof(struct DDS_HEADER_DXT10));
			default:
				std::cout << "ERROR: unsupported compression\n";
				delete[] (buffer);
				delete[] (header);
				fclose(f);
				return Texture2D();
		}
	} else {  // BC4U/BC4S/ATI2/BC55/R8G8_B8G8/G8R8_G8B8/UYVY-packed/YUY2-packed unsupported
		std::cout << "ERROR: unsupported compression\n";
		delete[] (buffer);
		delete[] (header);
		fclose(f);
		return Texture2D();
	}

	// allocate new unsigned char space with file_size - (file_code + header_size) magnitude
	// read rest of file
	buffer = new unsigned char[file_size - 128];
	if (buffer == 0) {
		std::cout << "ERROR: malloc failed\n";
		delete[] (buffer);
		delete[] (header);
		fclose(f);
		return Texture2D();
	}
	fread(buffer, 1, file_size, f);

	// now generate texture
	Texture2D texture;
	texture.Generate(width, height, format, mipMapCount, blockSize, buffer);

	Textures[name] = texture;

	delete[] (buffer);
	delete[] (header);
	fclose(f);
	return texture;
}

Texture2D ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	// (properly) delete all shaders
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.getID());
	// (properly) delete all textures
	for (auto iter : Textures) {
		GLuint id = iter.second.getID();
		glDeleteTextures(1, &id);
	}
}

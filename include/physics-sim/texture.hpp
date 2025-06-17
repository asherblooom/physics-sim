#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
private:
	// holds the ID of the texture object, used for all texture operations to reference to this particular texture
	GLuint ID;
	unsigned int Width, Height;	   // width and height of loaded image in pixels
	unsigned int Internal_Format;  // format of texture object
	// texture configuration
	unsigned int Wrap_S;	  // wrapping mode on S axis
	unsigned int Wrap_T;	  // wrapping mode on T axis
	unsigned int Filter_Min;  // filtering mode if texture pixels < screen pixels
	unsigned int Filter_Max;  // filtering mode if texture pixels > screen pixels
public:
	// constructor (sets default texture modes)
	Texture2D();
	// generates texture from image data
	void Generate(unsigned int width, unsigned int height, unsigned int format, unsigned int mipMapCount, unsigned int blockSize, unsigned char* data);
	// binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;

	GLuint getID() { return ID; }
};

#endif

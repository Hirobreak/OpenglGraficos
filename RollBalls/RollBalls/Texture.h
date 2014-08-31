#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>

class Texture{

public:
	Texture(GLenum textureTarget, const std::string& fileName);

	bool load();

	void bind(GLenum textureUnit);

private:
	std::string m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
};

#endif
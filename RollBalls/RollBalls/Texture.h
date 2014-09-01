#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>

class Texture{

public:
	Texture(GLenum textureTarget, const char *fileName);

	bool load();

	void bind(GLenum textureUnit);

private:
	const char *m_fileName;
	GLenum m_textureTarget;
	GLuint m_textureObj;
};

#endif
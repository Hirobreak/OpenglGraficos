#include <iostream>
#include "Texture.h"

Texture::Texture(GLenum textureTarget, const std::string& fileName){
	m_textureTarget = textureTarget;
	m_fileName = fileName;
}

bool Texture::load(){
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int size;
	unsigned char *data;
	FILE *file = fopen("test.bmp", "rb");
	if (!file){
		printf("Image couldnt open");
		return false;
	}
	if (fread(header, 1, 54, file)!=54){
		printf("Not a correct file");
		return false;
	}
	if (header[0]!='B' || header[1]!='M'){
		printf("not a correct file");
	}

	dataPos = *(int*)&(header[0x0A]);
	size = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (size==0){
		size=width*height*3;
	}
	if (dataPos==0){
		dataPos=54;
	}
	data = new unsigned char[size];
	fread(data, 1, size, file);
	fclose(file);

	glGenTextures(1, &m_textureObj);
	glBindTexture(m_textureTarget, m_textureObj);
	glTexImage2D(m_textureTarget, 0, GL_RGB, width,height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}

void Texture::bind(GLenum textureUnit){
	glActiveTexture(textureUnit);
	glBindTexture(m_textureTarget, m_textureObj);
}
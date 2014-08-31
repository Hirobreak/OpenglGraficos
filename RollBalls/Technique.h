#ifndef TECHNIQUE_H
#define	TECHNIQUE_H

#include <list>
#include <GL/glew.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

class Technique{
public:
	Technique();

	virtual ~Technique();

	virtual bool init();

	void enable();

protected:

	bool addShader(GLuint ShaderProgram, const char* pShaderText);

	bool finalize();

	GLint getUnifLocation(const char* pUniformName);

	GLint getProgramParam(GLint param);

	GLuint m_shaderProg;

private:

	typedef std::list<GLuint> ShaderObjList;
	ShaderObjList m_shaderObjList;

};

#endif
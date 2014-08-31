#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Technique.h"

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

bool loadShader(const std::string &fileName, std::string &out){
	
	std::ifstream file;
	file.open((fileName).c_str());
	std::string line;
	if(file.is_open()){
		while(file.good()){
			getline(file, line);
			out.append(line + "\n");
		}
	}else{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
		return false;
	}
	return true;
}

Technique::Technique(){
	m_shaderProg = 0;
}

Technique::~Technique(){
	for (ShaderObjList::iterator it = m_shaderObjList.begin(); it !=m_shaderObjList.end(); it++){
		glDeleteShader(*it);
	}
	if (m_shaderProg!=0){
		glDeleteProgram(m_shaderProg);
		m_shaderProg = 0;
	}
}

bool Technique::init(){
	m_shaderProg = glCreateProgram();

	if (m_shaderProg==0){
		printf("Error shader");
		return false;
	}

	return true;
}

bool Technique::addShader(GLenum ShaderType, const char* pFile){
	
	std::string s;
	
	if(!loadShader(pFile, s)){
		return false;
	}
	
	GLuint ShaderObj = glCreateShader(ShaderType);

	if(ShaderObj == 0)
		std::cerr << "Error compiling shader type " << ShaderType << std::endl;

	const GLchar* p[1];
	p[0] = s.c_str();
	GLint Lengths[1]={(GLint)s.size()};
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (success==0){
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		return false;
	}

	glAttachShader(m_shaderProg, ShaderObj);

	return true;
}

bool Technique::finalize(){
	GLint Success = 0;
	GLchar ErrorLog[1024] = {0};

	glLinkProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
	if (Success==0){
		glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		getchar();
        //exit(1);
	}

	glValidateProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);

	if (Success==0){
		glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		getchar();
        exit(1);
	}

	for (ShaderObjList::iterator it = m_shaderObjList.begin(); it !=m_shaderObjList.end(); it++){
		glDeleteShader(*it);
	}

	m_shaderObjList.clear();

	return GLCheckError();

}

void Technique::enable(){
	glUseProgram(m_shaderProg);
}

GLint Technique::getUnifLocation(const char* pUniformName){
	GLuint location = glGetUniformLocation(m_shaderProg, pUniformName);

	if (location == INVALID_UNIFORM_LOCATION){
		printf("Unable to locate %s", pUniformName);
		getchar();
	}

	return location;
}

GLint Technique::getProgramParam(GLint param){
	GLint ret;
	glGetProgramiv(m_shaderProg, param, &ret);
	return ret;
}
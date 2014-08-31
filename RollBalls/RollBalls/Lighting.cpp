#include "Lighting.h"

Lighting::Lighting(){

}

bool Lighting::init(){
	if(!Technique::init()){
		return false;
	}

	if(!addShader(GL_VERTEX_SHADER, "lighting.vs")){
		return false;
	}

	if(!addShader(GL_FRAGMENT_SHADER, "lighting.fs")){
		return false;
	}

	if (!finalize()){
		return false;
	}

	m_WVPLocation = getUnifLocation("gWVP");
	m_samplerLocation = getUnifLocation("gSampler");
	m_dirLightColorLocation = getUnifLocation("gDirectionalLight.Color");
	m_dirLightAmbientIntensityLocation = getUnifLocation("gDirectionalLight.AmbientIntensity");

	if (m_dirLightAmbientIntensityLocation == 0xFFFFFFFF || m_samplerLocation == 0xFFFFFFFF || m_dirLightColorLocation == 0xFFFFFFFF || m_WVPLocation == 0xFFFFFFFF){
		return false;
	}

	return true;
}

void Lighting::setWVP(const Matrix4f &WVP){
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void Lighting::setTextureUnit(unsigned int textureUnit){
	glUniform1i(m_samplerLocation, textureUnit);
}

void Lighting::setDirLight(const DirectionalLight &light){
	glUniform3f(m_dirLightColorLocation, light.Color.x, light.Color.y, light.Color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, (GLfloat)light.AmbientIntensity);
}
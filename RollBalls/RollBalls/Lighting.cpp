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
	m_WorldMatrixLocation = getUnifLocation("gWorld");
	m_samplerLocation = getUnifLocation("gSampler");
	m_dirLightLocation.color = getUnifLocation("gDirectionalLight.Color");
	m_dirLightLocation.ambient = getUnifLocation("gDirectionalLight.AmbientIntensity");
	m_dirLightLocation.direction = getUnifLocation("gDirectionalLight.Direction");
	m_dirLightLocation.diffuse = getUnifLocation("gDirectionalLight.DiffuseIntensity");

	if (m_dirLightLocation.color == 0xFFFFFFFF || m_samplerLocation == 0xFFFFFFFF || m_WorldMatrixLocation == 0xFFFFFFFF || m_WVPLocation == 0xFFFFFFFF ||
		m_dirLightLocation.ambient == 0xFFFFFFFF || m_dirLightLocation.diffuse == 0xFFFFFFFF || m_dirLightLocation.direction == 0xFFFFFFFF){
		return false;
	}

	return true;
}

void Lighting::setWVP(const Matrix4f &WVP){
	glUniformMatrix4fv(m_WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void Lighting::setWorldMatrix(const Matrix4f &WorldIn){
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldIn.m);
}

void Lighting::setTextureUnit(unsigned int textureUnit){
	glUniform1i(m_samplerLocation, textureUnit);
}

void Lighting::setDirLight(const DirectionalLight &light){
	glUniform3f(m_dirLightLocation.color, light.Color.x, light.Color.y, light.Color.z);
	glUniform1f(m_dirLightLocation.ambient, (GLfloat)light.AmbientIntensity);
	Vector3f direction = light.Direction;
	direction.Normalize();
	glUniform3f(m_dirLightLocation.direction, light.Direction.x, light.Direction.y, light.Direction.z);
	glUniform1f(m_dirLightLocation.diffuse, (GLfloat)light.DiffuseIntensity);
}
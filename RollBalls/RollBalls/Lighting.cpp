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
	m_eyeWorld = getUnifLocation("gEyeWorldPos");
	m_samplerLocation = getUnifLocation("gSampler");
	m_dirLightLocation.color = getUnifLocation("gDirectionalLight.Base.Color");
	m_dirLightLocation.ambient = getUnifLocation("gDirectionalLight.Base.AmbientIntensity");
	m_dirLightLocation.direction = getUnifLocation("gDirectionalLight.Direction");
	m_dirLightLocation.diffuse = getUnifLocation("gDirectionalLight.Base.DiffuseIntensity");
	m_SpecIntenLocation = getUnifLocation("gMatSpecularIntensity");
	m_SpecPowerLocation = getUnifLocation("gSpecularPower");
	m_numPointLightsLocation = getUnifLocation("gNumPointLights");

	if (m_dirLightLocation.color == 0xFFFFFFFF || m_samplerLocation == 0xFFFFFFFF || m_WorldMatrixLocation == 0xFFFFFFFF || m_WVPLocation == 0xFFFFFFFF ||
		m_dirLightLocation.ambient == 0xFFFFFFFF || m_dirLightLocation.diffuse == 0xFFFFFFFF || m_dirLightLocation.direction == 0xFFFFFFFF
		|| m_eyeWorld == 0xFFFFFFFF || m_SpecIntenLocation == 0xFFFFFFFF || m_SpecPowerLocation == 0xFFFFFFFF){
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

void Lighting::setEyeWorldPos(const Vector3f &eyeWorldPos){
	glUniform3f(m_eyeWorld, eyeWorldPos.x, eyeWorldPos.y, eyeWorldPos.z);
}

void Lighting::setMatSpecInten(float intensity){
	glUniform1f(m_SpecIntenLocation, intensity);
}

void Lighting::setMatSpecPower(float power){
	glUniform1f(m_SpecPowerLocation, power);
}

void Lighting::SetPointLights(unsigned int NumLights, const PointLight* pLights)
{
	glUniform1i(m_numPointLightsLocation, NumLights);

	for (unsigned int i = 0; i < NumLights; i++) {
		glUniform3f(m_pointLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_pointLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_pointLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_pointLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		glUniform1f(m_pointLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_pointLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_pointLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}

void Lighting::SetSpotLights(unsigned int NumLights, const SpotLight* pLights)
{
	glUniform1i(m_numSpotLightsLocation, NumLights);

	for (unsigned int i = 0; i < NumLights; i++) {
		glUniform3f(m_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
		glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
		glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
		glUniform3f(m_spotLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
		Vector3f Direction = pLights[i].Direction;
		Direction.Normalize();
		glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
		glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
		glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_spotLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_spotLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}
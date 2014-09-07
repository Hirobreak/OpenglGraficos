#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "Technique.h"
#include "math_3d.h"

struct BaseLight
{
	Vector3f Color;
	float AmbientIntensity;
	float DiffuseIntensity;

	BaseLight()
	{
		Color = Vector3f(0.0f, 0.0f, 0.0f);
		AmbientIntensity = 0.0f;
		DiffuseIntensity = 0.0f;
	}
};

struct DirectionalLight : public BaseLight
{
	Vector3f Direction;

	DirectionalLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
	}
};

struct PointLight : public BaseLight
{
	Vector3f Position;

	struct
	{
		float Constant;
		float Linear;
		float Exp;
	} Attenuation;

	PointLight()
	{
		Position = Vector3f(0.0f, 0.0f, 0.0f);
		Attenuation.Constant = 1.0f;
		Attenuation.Linear = 0.0f;
		Attenuation.Exp = 0.0f;
	}
};

struct SpotLight : public PointLight
{
	Vector3f Direction;
	float Cutoff;

	SpotLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
		Cutoff = 0.0f;
	}
};

class Lighting : public Technique{
public:

	static const unsigned int MAX_POINT_LIGHTS = 2;
	static const unsigned int MAX_SPOT_LIGHTS = 2;

	Lighting();

	virtual bool init();

	void setWVP(const Matrix4f &WVP);
	void setWorldMatrix(const Matrix4f &WorldIn);
	void setTextureUnit(unsigned int TextureUnit);
	void setDirLight(const DirectionalLight &light);
	void SetPointLights(unsigned int NumLights, const PointLight* pLights);
	void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
	void setEyeWorldPos(const Vector3f &eyeWorld);
	void setMatSpecInten(float intensity);
	void setMatSpecPower(float Power);

private:

	GLuint m_WVPLocation;
	GLuint m_samplerLocation;
	GLuint m_WorldMatrixLocation;
	GLuint m_eyeWorld;
	GLuint m_SpecIntenLocation;
	GLuint m_SpecPowerLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_numSpotLightsLocation;

	struct {
		GLuint color;
		GLuint ambient;
		GLuint direction;
		GLuint diffuse;
	} m_dirLightLocation;

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		struct
		{
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_pointLightsLocation[MAX_POINT_LIGHTS];

	struct {
		GLuint Color;
		GLuint AmbientIntensity;
		GLuint DiffuseIntensity;
		GLuint Position;
		GLuint Direction;
		GLuint Cutoff;
		struct {
			GLuint Constant;
			GLuint Linear;
			GLuint Exp;
		} Atten;
	} m_spotLightsLocation[MAX_SPOT_LIGHTS];
};

#endif
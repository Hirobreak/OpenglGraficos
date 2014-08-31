#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "Technique.h"
#include "math_3d.h"

struct DirectionalLight{
	Vector3f Color;
	float AmbientIntensity;
};

class Lighting : public Technique{
public:
	Lighting();

	virtual bool init();

	void setWVP(const Matrix4f &WVP);
	void setTextureUnit(unsigned int TextureUnit);
	void setDirLight(const DirectionalLight &light);

private:

	GLuint m_WVPLocation;
	GLuint m_samplerLocation;
	GLuint m_dirLightColorLocation;
	GLuint m_dirLightAmbientIntensityLocation;

};

#endif
#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "Technique.h"
#include "math_3d.h"

struct DirectionalLight{
	Vector3f Color;
	float AmbientIntensity;
	Vector3f Direction;
	float DiffuseIntensity;
};

class Lighting : public Technique{
public:
	Lighting();

	virtual bool init();

	void setWVP(const Matrix4f &WVP);
	void setWorldMatrix(const Matrix4f &WorldIn);
	void setTextureUnit(unsigned int TextureUnit);
	void setDirLight(const DirectionalLight &light);

private:

	GLuint m_WVPLocation;
	GLuint m_samplerLocation;
	GLuint m_WorldMatrixLocation;

	struct {
		GLuint color;
		GLuint ambient;
		GLuint direction;
		GLuint diffuse;
	} m_dirLightLocation;

};

#endif
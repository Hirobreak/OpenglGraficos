
#ifndef PIPELINE_H
#define	PIPELINE_H

#include "math_3d.h"

class Pipeline{
	
public:
	Pipeline(){
		m_scale = Vector3f(1.0f, 1.0f, 1.0f);
		m_worldPos = Vector3f(0.0f, 0.0f, 0.0f);
		m_rotate = Vector3f(0.0f, 0.0f, 0.0f);
	}

	void Scale(float X, float Y, float Z){
		m_scale.x=X;
		m_scale.y=Y;
		m_scale.z=Z;
	}

	void WorldPos(float x, float y, float z){
		m_worldPos.x=x;
		m_worldPos.y=y;
		m_worldPos.z=z;
	}

	void Rotate(float rx, float ry, float rz){
		m_rotate.x=rx;
		m_rotate.y=ry;
		m_rotate.z=rz;
	}

	void setCamera(const Vector3f &pos, const Vector3f &targ, const Vector3f &up){
		m_camera.pos=pos;
		m_camera.target=targ;
		m_camera.up=up;
	}
	void SetPerspectiveProj(float FOV, float width, float height, float znear, float zfar){
		m_persProj.FOV=FOV;
		m_persProj.width=width;
		m_persProj.height=height;
		m_persProj.znear=znear;
		m_persProj.zfar=zfar;
	}

	const Matrix4f& getWVPTrans();
	const Matrix4f& getWorldTrans();

private:

	Vector3f m_scale;
	Vector3f m_worldPos;
	Vector3f m_rotate;

	struct {
		float FOV;
		float width;
		float height;
		float znear;
		float zfar;
	} m_persProj;

	struct {
		Vector3f pos;
		Vector3f target;
		Vector3f up;
	} m_camera;

	Matrix4f m_WVPtransformation;
	Matrix4f m_worldTransform;
};

#endif
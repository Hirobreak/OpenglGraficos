
#include "Pipeline.h"

const Matrix4f& Pipeline::getWorldTrans(){
	Matrix4f scaleTrans, rotateTrans, traslaTrans;

	scaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
    rotateTrans.InitRotateTransform(m_rotate.x, m_rotate.y, m_rotate.z);
    traslaTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
	
	m_worldTransform = traslaTrans*rotateTrans*scaleTrans;

	return m_worldTransform;
}

const Matrix4f& Pipeline::getWVPTrans(){
	
	getWorldTrans();
	Matrix4f cameraTrans, cameraRot, persProjTrans;

	cameraTrans.InitTranslationTransform(-m_camera.pos.x, -m_camera.pos.y, -m_camera.pos.z);
	cameraRot.InitCameraTransform(m_camera.target, m_camera.up);
	persProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.width, m_persProj.height, m_persProj.znear, m_persProj.zfar);

	m_WVPtransformation = persProjTrans*cameraRot*cameraTrans*m_worldTransform;

	return m_WVPtransformation;
}


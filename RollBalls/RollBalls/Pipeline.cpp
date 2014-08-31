
#include "Pipeline.h"

const Matrix4f& Pipeline::GetTrans(){
	Matrix4f scaleTrans, rotateTrans, traslaTrans, cameraTrans, cameraRot, persProjTrans;

	scaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
    rotateTrans.InitRotateTransform(m_rotate.x, m_rotate.y, m_rotate.z);
    traslaTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
	cameraTrans.InitTranslationTransform(-m_camera.pos.x, -m_camera.pos.y, -m_camera.pos.z);
	cameraRot.InitCameraTransform(m_camera.target, m_camera.up);
	persProjTrans.InitPersProjTransform(m_persProj.FOV, m_persProj.width, m_persProj.height, m_persProj.znear, m_persProj.zfar);

	m_transformation = persProjTrans*cameraRot*cameraTrans*traslaTrans*rotateTrans*scaleTrans;

	return m_transformation;
}

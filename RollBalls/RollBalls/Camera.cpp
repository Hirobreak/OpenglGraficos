#include <GL\glut.h>
#include "Camera.h"
#include "math_3d.h"

const static float stepScale = 0.1f;
const static int MARGIN = 10;

Camera::Camera(){
	m_pos = Vector3f(0.0f, 0.0f, 0.0f);
	m_target = Vector3f(0.0f, 0.0f, 1.0f);
	m_up = Vector3f(0.0f, 1.0f, 0.0f);
}

Camera::Camera(int windoww, int windowh){
	m_windoww=windoww;
	m_windowh=windowh;
	m_pos = Vector3f(0.0f, 0.0f, 0.0f);
	m_target = Vector3f(0.0f, 0.0f, 1.0f);
	m_target.Normalize();
	m_up = Vector3f(0.0f, 1.0f, 0.0f);
	init();
}

Camera::Camera(const Vector3f & pos, const Vector3f &target, const Vector3f &up){
	m_pos = pos;
	m_target=target;
	m_target.Normalize();
	m_up = up;
	m_up.Normalize();
}

Camera::Camera(int windoww, int windowh, const Vector3f & pos, const Vector3f &target, const Vector3f &up){
	m_windoww=windoww;
	m_windowh=windowh;
	m_pos = pos;
	m_target = target;
	m_target.Normalize();
	m_up = up;
	m_up.Normalize();
	init();
}

void Camera::init(){
	Vector3f hTarget(m_target.x, 0.0, m_target.z);
	hTarget.Normalize();

	if (hTarget.z >= 0.0f){
		if (hTarget.x >= 0.0f){
			m_Angleh = 360.0f - ToDegree(asin(hTarget.z));
		}else{
			m_Angleh = 180.0f + ToDegree(asin(hTarget.z));
		}
	}else{
		if (hTarget.x >= 0.0f){
			m_Angleh =ToDegree(asin(-hTarget.z));
		}else{
			m_Angleh = 90.0f + ToDegree(asin(-hTarget.z));
		}
	}

	m_Anglev = -ToDegree(asin(m_target.y));

	bool m_OnupEdge=false;
	bool m_OnlowEdge=false;
	bool m_OnleftEdge=false;
	bool m_OnrightEdge=false;
	m_mousePos.x=m_windoww/2;
	m_mousePos.y=m_windowh/2;

	glutWarpPointer(m_mousePos.x, m_mousePos.y);
}

bool Camera::onKeyboard(int key){
	bool ret = false;

	switch(key){
	case GLUT_KEY_UP:
		{
			m_pos.x += (m_target.x*stepScale);
			m_pos.y += (m_target.y*stepScale);
			m_pos.z += (m_target.z*stepScale);
			ret=true;
		}
		break;
	case GLUT_KEY_DOWN:
		{
			m_pos.x -= (m_target.x*stepScale);
			m_pos.y -= (m_target.y*stepScale);
			m_pos.z -= (m_target.z*stepScale);
			ret=true;
		}
		break;
	case GLUT_KEY_LEFT:
		{
			Vector3f left = m_target.Cross(m_up);
			left.Normalize();
			left.x*=stepScale;
			left.y*=stepScale;
			left.z*=stepScale;
			m_pos.x+=left.x;
			m_pos.y+=left.y;
			m_pos.z+=left.z;
			ret=true;
		}
		break;
	case GLUT_KEY_RIGHT:
		{
			Vector3f right = m_target.Cross(m_up);
			right.Normalize();
			right.x*=stepScale;
			right.y*=stepScale;
			right.z*=stepScale;
			m_pos.x-=right.x;
			m_pos.y-=right.y;
			m_pos.z-=right.z;
			ret=true;
		}
		break;
	}

	return ret;
}

void Camera::onMouse(int x, int y){
	const int deltaX = x - m_mousePos.x;
	const int deltaY = y - m_mousePos.y;

	m_mousePos.x = x;
	m_mousePos.y = y;

	m_Angleh += (float)deltaX/20.0f;
	m_Anglev += (float)deltaY/20.0f;

	if (deltaX == 0){
		if (x<=MARGIN){
			m_OnleftEdge = true;
		}else if(x>=(m_windoww - MARGIN)){
			m_OnrightEdge=true;
		}
	} else {
		m_OnleftEdge=false;
		m_OnrightEdge=false;
	}

	if (deltaY == 0){
		if (y<=MARGIN){
			m_OnupEdge = true;
		}else if(y>=(m_windowh - MARGIN)){
			m_OnlowEdge=true;
		}
	} else {
		m_OnupEdge=false;
		m_OnlowEdge=false;
	}

	update();
}

void Camera::onRender(){
	bool shouldUpdate = false;

	if (m_OnleftEdge){
		m_Angleh-=0.1f;
		shouldUpdate=true;
	}else if (m_OnrightEdge){
		m_Angleh-=0.1f;
		shouldUpdate=true;
	}

	if (m_OnupEdge){
		if (m_Anglev > -90.0f){
			m_Anglev -= 0.1f;
			shouldUpdate = true;
		}
	}else if (m_OnlowEdge){
		if (m_Anglev < 90.0f){
			m_Anglev += 0.1f;
			shouldUpdate = true;
		}
	}

	if (shouldUpdate){
		update();
	}

}

void Camera::update(){
	const Vector3f vaxis(0.0f, 1.0f, 0.0f);

	Vector3f view(1.0f, 0.0f, 0.0f);
	view.Rotate(m_Angleh, vaxis);
	view.Normalize();

	Vector3f haxis = vaxis.Cross(view);
	haxis.Normalize();
	view.Rotate(m_Anglev, haxis);

	m_target = view;
	m_target.Normalize();
	
	m_up = m_target.Cross(haxis);
	m_up.Normalize();
}






#ifndef CAMERA_H
#define	CAMERA_H

#include "math_3d.h"

class Camera{
public:
	Camera();
	Camera(const Vector3f & pos, const Vector3f &target, const Vector3f &up);
	Camera(int windoww, int windowh);
	Camera(int windoww, int windowh, const Vector3f & pos, const Vector3f &target, const Vector3f &up);
	void onMouse(int x,int y);
	void onRender();
	bool onKeyboard(int key);
	const Vector3f& getPos() const{
		return m_pos;
	}
	const Vector3f& getTarget() const{
		return m_target;
	}
	const Vector3f& getUp() const{
		return m_up;
	}


private:

	void init();
	void update();

	Vector3f m_pos;
	Vector3f m_target;
	Vector3f m_up;

	int m_windoww;
	int m_windowh;
	float m_Angleh;
	float m_Anglev;
	bool m_OnupEdge;
	bool m_OnlowEdge;
	bool m_OnleftEdge;
	bool m_OnrightEdge;

	Vector2i m_mousePos;

};

#endif
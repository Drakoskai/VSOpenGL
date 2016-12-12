#pragma once
#include "../InputHandler.h"
#include "Camera.h";

class CameraMouseInputListener : public MouseInputListner
{
public: 
	CameraMouseInputListener(View::Camera* camera);
	~CameraMouseInputListener();

	void OnMouseMoveEvent(GLFWwindow* window, double xpos, double ypos) override;
	void Update(float deltaTime) override;

private:
	View::Camera* m_camera;
	double m_curX;
	double m_curY;

};

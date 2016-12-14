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
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	float m_lastY;
	float m_lastX;
	float m_init;

	float m_sensitivity;
};

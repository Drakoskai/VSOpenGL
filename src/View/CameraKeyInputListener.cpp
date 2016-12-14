#include "../pch.h"
#include "CameraKeyInputListener.h"

CameraKeyListener::CameraKeyListener(View::Camera* camera)
	: m_camera(camera), m_forward(false), m_backward(false), m_upward(false), m_downward(false),
	m_left(false), m_right(false) { }

CameraKeyListener::~CameraKeyListener() { }

void CameraKeyListener::Update(float deltaTime)
{
	Math3d::Vector4f position = m_camera->GetPosition();
	Math3d::Vector4f forward = m_camera->GetRotation().GetForward();
	Math3d::Vector4f right = m_camera->GetRotation().GetRight();
	Math3d::Vector4f up = m_camera->GetRotation().GetUp();

	float speed = 5.0f * deltaTime;
	if (m_forward) { position += forward * speed; }
	if (m_backward) { position -= forward * speed; }
	if (m_left) { position += right * speed; }
	if (m_right) { position -= right * speed; }
	if (m_upward) { position -= up * speed; }
	if (m_downward) { position += up * speed; }

	m_camera->SetPosition(position);
}

void CameraKeyListener::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_right = true;
			break;
		case GLFW_KEY_A:
			m_left = true;
			break;
		case GLFW_KEY_W:
			m_forward = true;
			break;
		case GLFW_KEY_S:
			m_backward = true;
			break;
		case GLFW_KEY_SPACE:
			m_upward = true;
			break;
		case GLFW_KEY_Z:
			m_downward = true;
			break;
		default: break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_D:
			m_right = false;
			break;
		case GLFW_KEY_A:
			m_left = false;
			break;
		case GLFW_KEY_W:
			m_forward = false;
			break;
		case GLFW_KEY_S:
			m_backward = false;
			break;
		case GLFW_KEY_SPACE:
			m_upward = false;
			break;
		case GLFW_KEY_Z:
			m_downward = false;
			break;
		default: break;
		}
	}
}

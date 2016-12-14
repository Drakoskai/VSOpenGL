#include "../pch.h"
#include "CameraMouseInputListener.h"
#include "../GL/GLDevice.h"

CameraMouseInputListener::CameraMouseInputListener(View::Camera* camera)
	: m_camera(camera), m_rotationX(0), m_rotationY(0), m_rotationZ(0), m_lastY(0), m_lastX(0), m_init(true), m_sensitivity(0.05f) { }

CameraMouseInputListener::~CameraMouseInputListener() { }

void CameraMouseInputListener::OnMouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
	if (m_init)
	{
		m_lastY = ypos;
		m_lastX = xpos;
		m_init = false;

	}

	float offsety = m_lastY - ypos;
	float offsetx = m_lastX - xpos;
	m_rotationX += offsetx * m_sensitivity;
	m_rotationY += offsety * m_sensitivity;

	m_lastY = ypos;
	m_lastX = xpos;

	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}
}

void CameraMouseInputListener::Update(float deltaTime)
{
	Math3d::Quaternion heading = Math3d::Quaternion::FromAxisAngle(Math3d::Angle::FromDegrees(m_rotationX), Math3d::Vector4f::UnitY);
	Math3d::Quaternion pitch = Math3d::Quaternion::FromAxisAngle(Math3d::Angle::FromDegrees(m_rotationY), Math3d::Vector4f::UnitX);
	Math3d::Quaternion roll = Math3d::Quaternion::FromAxisAngle(Math3d::Angle::FromDegrees(m_rotationZ), Math3d::Vector4f::UnitZ);
	Math3d::Quaternion orientation = pitch * heading * roll;

	m_camera->SetRotation(orientation);
}

#include "../pch.h"
#include "CameraKeyInputListener.h"

CameraKeyListener::CameraKeyListener(View::Camera* camera)
	: m_camera(camera), m_forward(false), m_backward(false), m_upward(false), m_downward(false),
	m_left(false), m_right(false), m_forwardSpeed(0), m_backwardSpeed(0), m_upwardSpeed(0),
	m_downwardSpeed(0), m_leftStrafeSpeed(0), m_rightStrafeSpeed(0) { }

CameraKeyListener::~CameraKeyListener() { }

void CameraKeyListener::Update(float deltaTime)
{
	float speedCoefficent = 35.0f;
	float dragCoefficent = 1.0f;

	Math3d::Vector4f pos = m_camera->
		GetTransform()
		.GetPosition();

	Math3d::Angle angle = m_camera->
		GetTransform()
		.GetRotation()
		.GetRotationY();

	float positionX = pos.x;
	float positionY = pos.y;
	float positionZ = pos.z;

	if (m_right)
	{
		m_rightStrafeSpeed += deltaTime * 1.0f;

		if (m_rightStrafeSpeed > deltaTime * speedCoefficent)
		{
			m_rightStrafeSpeed = deltaTime * speedCoefficent;
		}
		positionX -= angle.Cos() * m_rightStrafeSpeed;
		positionZ -= angle.Sin() * m_rightStrafeSpeed;
	}
	else
	{
		m_rightStrafeSpeed -= deltaTime * dragCoefficent;

		if (m_rightStrafeSpeed < 0.0f)
		{
			m_rightStrafeSpeed = 0.0f;
		}
		positionX -= angle.Cos() * m_rightStrafeSpeed;
		positionZ -= angle.Sin() * m_rightStrafeSpeed;
	}
	if (m_left)
	{
		m_leftStrafeSpeed += deltaTime * 1.0f;

		if (m_leftStrafeSpeed > deltaTime *speedCoefficent)
		{
			m_leftStrafeSpeed = deltaTime * speedCoefficent;
		}
		positionX += angle.Cos() * m_leftStrafeSpeed;
		positionZ += angle.Sin() * m_leftStrafeSpeed;
	}
	else
	{
		m_leftStrafeSpeed -= deltaTime * dragCoefficent;

		if (m_leftStrafeSpeed < 0.0f)
		{
			m_leftStrafeSpeed = 0.0f;
		}
		positionX += angle.Cos() * m_leftStrafeSpeed;
		positionZ += angle.Sin() * m_leftStrafeSpeed;
	}
	if (m_forward)
	{
		m_forwardSpeed += deltaTime * 1.0f;
		if (m_forwardSpeed > deltaTime * speedCoefficent)
		{
			m_forwardSpeed = deltaTime * speedCoefficent;
		}
		positionX += angle.Sin() * m_forwardSpeed;
		positionZ += angle.Cos() * m_forwardSpeed;
	}
	else
	{
		m_forwardSpeed -= deltaTime * dragCoefficent;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
		positionX += angle.Sin() * m_forwardSpeed;
		positionZ += angle.Cos() * m_forwardSpeed;
	}
	if (m_backward)
	{
		m_backwardSpeed += deltaTime * 1.0f;

		if (m_backwardSpeed > deltaTime * speedCoefficent)
		{
			m_backwardSpeed = deltaTime * speedCoefficent;
		}
		positionX -= angle.Sin() * m_backwardSpeed;
		positionZ -= angle.Cos() * m_backwardSpeed;
	}
	else
	{
		m_backwardSpeed -= deltaTime * dragCoefficent;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
		positionX -= angle.Sin() * m_backwardSpeed;
		positionZ -= angle.Cos() * m_backwardSpeed;
	}
	if (m_upward)
	{
		m_upwardSpeed += deltaTime * 1.5f;

		if (m_upwardSpeed > deltaTime * 15.0f)
		{
			m_upwardSpeed = deltaTime * 15.0f;
		}
		positionY += m_upwardSpeed;
	}
	else
	{
		m_upwardSpeed -= deltaTime * dragCoefficent;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
		positionY += m_upwardSpeed;
	}
	if (m_downward)
	{
		m_downwardSpeed += deltaTime * 1.5f;

		if (m_downwardSpeed > deltaTime * 15.0f)
		{
			m_downwardSpeed = deltaTime * 15.0f;
		}
		positionY -= m_downwardSpeed;
	}
	else
	{
		m_downwardSpeed -= deltaTime * dragCoefficent;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
		positionY -= m_downwardSpeed;
	}

	m_camera->GetTransform().SetPosition(positionX, positionY, positionZ);
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

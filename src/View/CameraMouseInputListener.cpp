#include "../pch.h"
#include "CameraMouseInputListener.h"
#include "../GL/GLDevice.h"

CameraMouseInputListener::CameraMouseInputListener(View::Camera* camera)
	: m_camera(camera), m_curX(0), m_curY(0) { }

CameraMouseInputListener::~CameraMouseInputListener() { }

void CameraMouseInputListener::OnMouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
	Util::DebugPrintF("Cursor position - X: %f, Y: %f\n", xpos, ypos);
}

void CameraMouseInputListener::Update(float deltaTime) { }

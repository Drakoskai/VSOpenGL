#include "Camera.h"
#include <GLFW/glfw3.h>

CameraSimpleOrtho::CameraSimpleOrtho() { }

CameraSimpleOrtho::~CameraSimpleOrtho() { }

void CameraSimpleOrtho::Update(float ratio)
{
	model.Identity();
	model *= Matrix::MakeRotationZ(static_cast<float>(glfwGetTime()));
	perspective = Matrix::MakeOrtho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);

	modelViewPerspective = perspective * model;
}

Matrix CameraSimpleOrtho::GetModelView() const
{
	return modelViewPerspective;
}

CameraPerspective::CameraPerspective()
	: m_frustum(), m_nearClip(Display::DefaultScreenNear), m_farClip(Display::DefaultScreenDepth),
	  m_fieldofView(Display::DefaultFieldOfView), m_screenAspect(Display::DefaultAspectRatio),
	  m_viewportWidth(Display::DefaultWidth), m_viewportHeight(Display::DefaultHeight)
{
	m_up = Vector3f::Up;
}

CameraPerspective::~CameraPerspective() { }

void CameraPerspective::Update()
{
	m_modelView = Matrix::MakeLookAt(m_position, m_lookAt, m_up);
	m_projection = Matrix::MakePerspective(m_fieldofView, m_screenAspect, m_nearClip, m_farClip);
	m_frustum = Frustum(m_fieldofView, m_viewportWidth, m_viewportHeight, m_nearClip, m_farClip);
}

void CameraPerspective::GetModelView(Matrix& modelView) const { modelView = m_modelView; }

void CameraPerspective::GetProjection(Matrix& projection) const { projection = m_projection; }

void CameraPerspective::GetPosition(Vector3f& pos) const { pos = m_position; }

void CameraPerspective::GetRotation(Vector3f& rot) const { rot = m_rotation; }

void CameraPerspective::GetUp(Vector3f& up) const { up = m_up; }

void CameraPerspective::GetForward(Vector3f& forward) const { forward = m_lookAt; }

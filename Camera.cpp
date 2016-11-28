#include "Camera.h"
#include <GLFW/glfw3.h>

CameraSimpleOrtho::CameraSimpleOrtho()
	: m_aspectRatio(0), m_viewportWidth(0), m_viewportHeight(0) { }

CameraSimpleOrtho::~CameraSimpleOrtho() { }

void CameraSimpleOrtho::Update(ViewProps viewProps)
{
	int width = viewProps.width;
	int height = viewProps.height;
	if (height != m_viewportHeight || width != m_viewportWidth)
	{
		m_aspectRatio = width / static_cast<float>(height);
		
	}

	m_model.Identity();
	m_model *= Matrix::MakeRotationZ(static_cast<float>(glfwGetTime()));
	m_perspective = Matrix::MakeOrtho(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, 1.0f, -1.0f);

	m_modelViewPerspective = m_perspective * m_model;
}

Matrix CameraSimpleOrtho::GetModelView() const
{
	return m_modelViewPerspective;
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

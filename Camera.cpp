#include "Camera.h"
#include <GL/glew.h>

Camera::Camera()
	: m_frustum(), m_nearClip(Display::DefaultScreenNear), m_farClip(Display::DefaultScreenDepth),
	  m_fieldofView(Display::DefaultFieldOfView), m_screenAspect(Display::DefaultAspectRatio),
	  m_viewportWidth(Display::DefaultWidth), m_viewportHeight(Display::DefaultHeight)
{
	m_up = Vector3f::Up;
}

Camera::~Camera() { }

void Camera::Update()
{
	m_modelView = Matrix::MakeLookAt(m_position, m_lookAt, m_up);
	m_projection = Matrix::MakePerspective(m_fieldofView, m_screenAspect, m_nearClip, m_farClip);
	m_frustum = Frustum(m_fieldofView, m_viewportWidth, m_viewportHeight, m_nearClip, m_farClip);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadMatrixf(m_modelView.mat);
	glMatrixMode(GL_PROJECTION);

	glLoadMatrixf(m_projection.mat);



}

void Camera::GetModelView(Matrix& modelView) const { modelView = m_modelView; }

void Camera::GetProjection(Matrix& projection) const { projection = m_projection; }

void Camera::GetPosition(Vector3f& pos) const { pos = m_position; }

void Camera::GetRotation(Vector3f& rot) const { rot = m_rotation; }

void Camera::GetUp(Vector3f& up) const { up = m_up; }

void Camera::GetForward(Vector3f& forward) const { forward = m_lookAt; }

#include "View.h"

Camera::Camera()
	: m_nearClip(Display::DefaultScreenNear), m_farClip(Display::DefaultScreenDepth),
	m_fieldofView(Display::DefaultFieldOfView), m_screenAspect(Display::DefaultAspectRatio),
	m_viewportWidth(Display::DefaultWidth), m_viewportHeight(Display::DefaultHeight) { }

Camera::~Camera() { }

void Camera::Init() { }

void Camera::Update() { }

void Camera::GetModelView(Matrix& modelView) const { modelView = m_modelView; }

void Camera::GetProjection(Matrix& projection) const { projection = m_projection; }

void Camera::GetPosition(Vector3f& pos) const { pos = m_position; }

void Camera::GetRotation(Vector3f& rot) const { rot = m_rotation; }

void Camera::GetUp(Vector3f& up) const { up = m_up; }

void Camera::GetForward(Vector3f& forward) const { forward = m_forward; }

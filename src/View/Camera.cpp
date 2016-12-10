#include "../pch.h"
#include "Camera.h"
#include "../Interfaces.h"

namespace View
{
	using namespace Math3d;

	Camera::Camera()
		: m_nearClip(DefaultScreenNear), m_farClip(DefaultScreenDepth),
		m_fieldofView(DefaultFieldOfView), m_screenAspect(DefaultAspectRatio),
		m_viewportWidth(DefaultWidth), m_viewportHeight(DefaultHeight)
	{
		m_proj = MakePerspectiveRH(Angle::FromDegrees(m_fieldofView), m_screenAspect, m_nearClip, m_farClip);
		m_lookAt = Vector4f::UnitZ;
		m_up = Vector4f::UnitY;
		Vector4f position = m_transform.GetPosition();
		Vector4f focus = position + m_lookAt;
		m_view = MakeLookAtRH(position, focus, m_up);
	}

	Camera::~Camera() { }

	void Camera::Update()
	{
		Vector4f position = m_transform.GetPosition();
		Vector4f focus = position + m_lookAt;
		m_view = MakeLookAtRH(position, focus, m_up);
	}

	Matrix Camera::GetView() const { return m_view; }

	Matrix Camera::GetProj() const { return m_proj; }

	void Camera::SetUp(const Vector4f& up) { m_up = up; }
	Vector4f Camera::GetUp() const { return m_up; }

	void Camera::SetLookAt(const Vector4f& lookat) { m_lookAt = lookat; }

	Vector4f Camera::GetLookAt() const { return m_lookAt; }

	Model::Transform& Camera::GetTransform() { return m_transform; }
}

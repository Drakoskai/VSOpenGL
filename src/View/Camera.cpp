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

		Vector4f focus = m_position + Vector4f::UnitZ;
		Vector4f up = Vector4f::UnitY;
		m_view = MakeLookAtRH(m_position, focus, up);
	}

	Camera::~Camera() { }

	void Camera::Update()
	{
		Vector4f focus = m_position + Vector4f::UnitZ;
		Vector4f up = Vector4f::UnitY;
		m_view = MakeLookAtRH(m_position, focus, up);
	}

	Matrix Camera::GetView() const { return m_view; }

	Matrix Camera::GetProj() const { return m_proj; }

	void Camera::SetPosition(const Vector4f& position) { m_position = position; }
	
	void Camera::SetPosition(const float x, const float y, const float z) { SetPosition(Vector4f(x, y, z)); }

	Vector4f Camera::GetPosition() const { return m_position; }

	void Camera::SetRotation(const Vector4f& rotation) { m_rotation = rotation; }

	Vector4f Camera::GetRotation() const { return m_rotation; }

	Vector4f Camera::GetUp() const { return m_up; }

	Vector4f Camera::GetForward() const { return m_lookAt; }
}

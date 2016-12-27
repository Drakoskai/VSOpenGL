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
		m_rotation = Quaternion::MakeLookAt(m_position, Vector4f::Forward);
		
		Vector3f focus = m_position + m_rotation.GetForward();
		m_view = MakeLookAtRH(m_position, focus, m_rotation.GetUp());
	}

	Camera::~Camera() { }

	void Camera::Update()
	{
		Vector3f focus = m_position + m_rotation.GetForward();

		m_view = MakeLookAtRH(m_position, focus, m_rotation.GetUp());
	}

	Matrix Camera::GetView() const { return m_view; }

	Matrix Camera::GetProj() const { return m_proj; }

	Vector3f Camera::GetPosition() const { return m_position; }

	Quaternion Camera::GetRotation() const	{ return m_rotation; }

	void Camera::SetPosition(const Vector3f& position) { m_position = position; }

	void Camera::SetPosition(const float x, const float y, const float z) { SetPosition(Vector3f(x, y, z)); }

	void Camera::SetRotation(const Quaternion& rotation) { m_rotation = rotation; }
}

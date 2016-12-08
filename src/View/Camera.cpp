#include "../pch.h"
#include "Camera.h"
#include "../Interfaces.h"

namespace View
{
	using namespace Math3d;

	CameraOrtho::CameraOrtho()
		: m_aspectRatio(0.0f), m_viewportWidth(DefaultWidth), m_viewportHeight(DefaultHeight)
	{
		m_aspectRatio = m_viewportWidth / static_cast<float>(m_viewportHeight);
		m_proj = MakeOrtho(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, 1.0f, -1.0f);
	}

	CameraOrtho::~CameraOrtho() { }

	void CameraOrtho::Update() 	{ }

	Matrix CameraOrtho::GetView() const
	{
		return m_view;
	}

	Math3d::Matrix CameraOrtho::GetProjection() const
	{
		return m_proj;
	}

	CameraPerspective::CameraPerspective()
		: m_nearClip(DefaultScreenNear), m_farClip(DefaultScreenDepth),
		m_fieldofView(DefaultFieldOfView), m_screenAspect(DefaultAspectRatio),
		m_viewportWidth(DefaultWidth), m_viewportHeight(DefaultHeight)
	{
		m_up = Vector3f::Up;
		m_proj = MakePerspective(m_fieldofView, m_screenAspect, m_nearClip, m_farClip);
	}

	CameraPerspective::~CameraPerspective() { }

	void CameraPerspective::Update()
	{
		m_view = MakeLookAt(m_position, m_lookAt, m_up);	
	}

	void CameraPerspective::GetView(Matrix& modelView) const { modelView = m_view; }

	void CameraPerspective::GetProjection(Matrix& projection) const { projection = m_proj; }

	void CameraPerspective::GetPosition(Vector3f& pos) const { pos = m_position; }

	void CameraPerspective::GetRotation(Vector3f& rot) const { rot = m_rotation; }

	void CameraPerspective::GetUp(Vector3f& up) const { up = m_up; }

	void CameraPerspective::GetForward(Vector3f& forward) const { forward = m_lookAt; }
}

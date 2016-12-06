#include "../pch.h"
#include "Camera.h"
#include "../Interfaces.h"

namespace View
{
	using namespace Math3d;

	CameraOrtho::CameraOrtho()
		: m_aspectRatio(0), m_viewportWidth(0), m_viewportHeight(0) { }

	CameraOrtho::~CameraOrtho() { }

	void CameraOrtho::Update(ViewProps viewProps)
	{
		int width = viewProps.width;
		int height = viewProps.height;
		if (height != m_viewportHeight || width != m_viewportWidth)
		{
			m_aspectRatio = width / static_cast<float>(height);
		}

		m_model.Identity();
		m_model *= MakeRotationZ(static_cast<float>(glfwGetTime()));
		m_perspective = MakeOrtho(-m_aspectRatio, m_aspectRatio, -1.0f, 1.0f, 1.0f, -1.0f);

		m_modelViewPerspective = m_perspective * m_model;
	}

	Matrix CameraOrtho::GetModelView() const
	{
		return m_modelViewPerspective;
	}

	CameraPerspective::CameraPerspective()
		: m_nearClip(DefaultScreenNear), m_farClip(DefaultScreenDepth),
		m_fieldofView(DefaultFieldOfView), m_screenAspect(DefaultAspectRatio),
		m_viewportWidth(DefaultWidth), m_viewportHeight(DefaultHeight)
	{
		m_up = Vector3f::Up;
	}

	CameraPerspective::~CameraPerspective() { }

	void CameraPerspective::Update()
	{
		m_modelView = MakeLookAt(m_position, m_lookAt, m_up);
		m_projection = MakePerspective(m_fieldofView, m_screenAspect, m_nearClip, m_farClip);
	}

	void CameraPerspective::GetModelView(Matrix& modelView) const { modelView = m_modelView; }

	void CameraPerspective::GetProjection(Matrix& projection) const { projection = m_projection; }

	void CameraPerspective::GetPosition(Vector3f& pos) const { pos = m_position; }

	void CameraPerspective::GetRotation(Vector3f& rot) const { rot = m_rotation; }

	void CameraPerspective::GetUp(Vector3f& up) const { up = m_up; }

	void CameraPerspective::GetForward(Vector3f& forward) const { forward = m_lookAt; }
}

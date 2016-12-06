#pragma once

#include "../Math3d/Vector.h"
#include "../Math3d/Matrix.h"

namespace View
{
	struct ViewProps
	{
		int width;
		int height;
	};

	class CameraOrtho
	{
	public:
		CameraOrtho();
		~CameraOrtho();

		void Update(ViewProps viewProps);
		Math3d::Matrix GetModelView() const;
	private:
		Math3d::Matrix m_model;
		Math3d::Matrix m_perspective;
		Math3d::Matrix m_modelViewPerspective;

		float m_aspectRatio;
		int m_viewportWidth;
		int m_viewportHeight;
	};

	class CameraPerspective
	{
	public:
		CameraPerspective();
		~CameraPerspective();

		void Update();

		void GetModelView(Math3d::Matrix& modelView) const;
		void GetProjection(Math3d::Matrix& projection) const;

		void GetPosition(Math3d::Vector3f& pos) const;
		void GetRotation(Math3d::Vector3f& rot) const;

		void GetUp(Math3d::Vector3f& up) const;
		void GetForward(Math3d::Vector3f& forward) const;

	private:
		Math3d::Matrix m_modelView;
		Math3d::Matrix m_projection;

		Math3d::Vector3f m_up;
		Math3d::Vector3f m_lookAt;
		Math3d::Vector3f m_position;
		Math3d::Vector3f m_rotation;

		float m_nearClip;
		float m_farClip;
		float m_fieldofView;
		float m_screenAspect;

		int m_viewportWidth;
		int m_viewportHeight;
	};
}

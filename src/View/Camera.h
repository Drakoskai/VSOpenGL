#pragma once

#include "../Math3d/Vector.h"
#include "../Math3d/Matrix.h"

namespace View
{
	class CameraOrtho
	{
	public:
		CameraOrtho();
		~CameraOrtho();

		void Update();
		Math3d::Matrix GetView() const;
		Math3d::Matrix GetProjection() const;
	private:
		Math3d::Matrix m_view;
		Math3d::Matrix m_proj;
		Math3d::Vector4f m_position;

		float m_aspectRatio;
		int m_viewportWidth;
		int m_viewportHeight;
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		void Update();

		Math3d::Matrix GetView() const;
		Math3d::Matrix GetProj() const;
		
		void SetPosition(const Math3d::Vector4f& position);
		void SetPosition(const float x, const float y, const float z);
		Math3d::Vector4f GetPosition() const;
		void SetRotation(const Math3d::Vector4f& rotation);
		Math3d::Vector4f GetRotation() const;

		Math3d::Vector4f GetUp() const;
		Math3d::Vector4f GetForward() const;

	private:
		Math3d::Matrix m_view;
		Math3d::Matrix m_proj;

		Math3d::Vector4f m_up;
		Math3d::Vector4f m_lookAt;
		Math3d::Vector4f m_position;
		Math3d::Vector4f m_rotation;

		float m_nearClip;
		float m_farClip;
		float m_fieldofView;
		float m_screenAspect;

		int m_viewportWidth;
		int m_viewportHeight;
	};
}

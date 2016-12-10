#pragma once

#include "../Math3d/Vector.h"
#include "../Math3d/Matrix.h"
#include "../Model/Transform.h"

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
		void SetUp(const Math3d::Vector4f& up);
		Math3d::Vector4f GetUp() const;
		void SetLookAt(const Math3d::Vector4f& forward);
		Math3d::Vector4f GetLookAt() const;
		Model::Transform& GetTransform();

	private:
		Math3d::Matrix m_view;
		Math3d::Matrix m_proj;
		Model::Transform m_transform;

		Math3d::Vector4f m_up;
		Math3d::Vector4f m_lookAt;

		float m_nearClip;
		float m_farClip;
		float m_fieldofView;
		float m_screenAspect;

		int m_viewportWidth;
		int m_viewportHeight;
	};
}

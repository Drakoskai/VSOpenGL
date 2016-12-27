#pragma once

#include "../Math3d/Vector.h"
#include "../Math3d/Matrix.h"
#include "../Model/Transform.h"

namespace View
{

	struct CameraViewState
	{
		float rotationX;
		float rotationY;
		float rotationZ;
	};

	class CameraOrtho
	{
	public:
		CameraOrtho();
		~CameraOrtho();

		void Update();
		Math3d::Matrix GetView() const;
		Math3d::Matrix GetProjection() const;

	private:
		CameraViewState m_cameraViewState;

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
		Math3d::Vector3f GetPosition() const;
		Math3d::Quaternion GetRotation() const;

		void SetPosition(const Math3d::Vector3f& position);
		void SetPosition(const float x, const float y, const float z);
		void SetRotation(const Math3d::Quaternion& rotation);

	private:
		Math3d::Matrix m_view;
		Math3d::Matrix m_proj;
		Math3d::Vector3f m_position;
		Math3d::Quaternion m_rotation;

		float m_nearClip;
		float m_farClip;
		float m_fieldofView;
		float m_screenAspect;

		int m_viewportWidth;
		int m_viewportHeight;
	};
}

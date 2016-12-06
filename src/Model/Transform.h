#pragma once

#include "../Math3d/Matrix.h"

namespace Model
{
	class Transform
	{
	public:
		Transform();
		~Transform();

		void Update();
		void Translate(Math3d::Vector3f vector);
		void Scale(Math3d::Vector3f vec);
		void RotateX(float theta);
		void RotateY(float theta);
		void RotateZ(float theta);
		Math3d::Matrix& GetModelMatrix();

	private:
		Math3d::Matrix m_scale;
		Math3d::Matrix m_trans;
		Math3d::Matrix m_rot;
		Math3d::Matrix m_model;
	};
}

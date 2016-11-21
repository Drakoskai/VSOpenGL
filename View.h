#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Interfaces.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void GetModelView(Matrix& modelView) const;
	void GetProjection(Matrix& projection) const;

	void GetPosition(Vector3f& pos) const;
	void GetRotation(Vector3f& rot) const;

	void GetUp(Vector3f& up) const;
	void GetForward(Vector3f& forward) const;

private:
	Matrix m_modelView;
	Matrix m_projection;

	Vector3f m_up;
	Vector3f m_forward;
	Vector3f m_position;
	Vector3f m_rotation;
	
	float m_nearClip;
	float m_farClip;
	float m_fieldofView;
	float m_screenAspect;

	float m_viewportWidth;
	float m_viewportHeight;

};

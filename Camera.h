#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Interfaces.h"

struct ViewProps
{
	int width;
	int height;
};

class CameraSimpleOrtho
{
public:
	CameraSimpleOrtho();
	~CameraSimpleOrtho();

	void Update(ViewProps viewProps);
	Matrix GetModelView() const;
private:
	Matrix m_model;
	Matrix m_perspective;
	Matrix m_modelViewPerspective;

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
	Vector3f m_lookAt;
	Vector3f m_position;
	Vector3f m_rotation;
	
	float m_nearClip;
	float m_farClip;
	float m_fieldofView;
	float m_screenAspect;

	int m_viewportWidth;
	int m_viewportHeight;

};

#include "Frustum.h"
#include "Geometry.h"

Frustum::Frustum()
	: leftPlane(), rightPlane(), bottomPlane(), topPlane(), nearPlane(), farPlane() { }

Frustum::Frustum(float fieldOfView, int width, int height, float nearClip, float farClip)
	: leftPlane(), rightPlane(), bottomPlane(), topPlane(), nearPlane(), farPlane()
{
	float horizontalFieldOfView = Geometry::DegToRad *fieldOfView;
	float focalLength = 1.0f / tan(horizontalFieldOfView * 0.5f);
	float aspect = height / static_cast<float>(width);
	float lrLen = sqrt(focalLength * focalLength + 1);
	float btLen = sqrt(focalLength * focalLength + aspect * aspect);

	leftPlane = Plane(focalLength / lrLen, 0.0f, 0.0f - 1.0f / lrLen, 0.0f);
	rightPlane = Plane(0.0f - focalLength / lrLen, 0.0f, 0.0f - 1.0f / lrLen, 0.0f);
	bottomPlane = Plane(0.0f, focalLength / btLen, 0.0f - aspect / btLen, 0.0f);
	topPlane = Plane(0.0f, 0.0f - focalLength / btLen, 0.0f - aspect / btLen, 0.0f);
	nearPlane = Plane(0.0f, 0.0f, 0.0f - 1.0f, 0.0f - nearClip);
	farPlane = Plane(0.0f, 0.0f, 1.0f, farClip);
}

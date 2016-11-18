#pragma once
#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>
#include "Matrix.h"

#pragma comment(lib, "glew32s.lib")
//#pragma comment(lib, "opengl32.lib")


class GLDeviceResources
{
public:
	GLDeviceResources();
	~GLDeviceResources();

	static bool Init(HWND hwnd);
	bool InitOpenGL(HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync);

	void Release(HWND hwnd);
	HDC GetDeviceContext() const;
	HGLRC GetRenderingContext() const;

	void GetWorldMatrix(Matrix& matrix) const;
	void GetProjMatrix(Matrix& matrix) const;
	void BuildPerspectiveFovLHMatrix(Matrix& matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth) const;

private:
	static bool InitializeExt(HWND hwnd);
	HDC m_deviceContext;
	HGLRC m_renderingContext;

	Matrix m_worldMatrix;
	Matrix m_projectionMatrix;

	HWND m_hWnd;
	HINSTANCE m_hInst;
};
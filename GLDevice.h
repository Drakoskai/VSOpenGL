#pragma once
#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>
#include "Matrix.h"
#include "Interfaces.h"

#pragma comment(lib, "glew32s.lib")

class GLDevice
{
public:
	GLDevice();
	~GLDevice();

	static bool Init(HWND hwnd);
	bool InitOpenGL(HWND hwnd, const DisplayState &displayState);

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



	HWND m_hWnd;
	HINSTANCE m_hInst;

};
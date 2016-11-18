#include "GLDeviceResources.h"
#include <math.h>


GLDeviceResources::GLDeviceResources()
	: m_deviceContext(nullptr), m_renderingContext(nullptr), m_hWnd(nullptr), m_hInst(nullptr) { }

GLDeviceResources::~GLDeviceResources() { }

bool GLDeviceResources::Init(HWND hwnd)
{
	HDC deviceContext;
	deviceContext = GetDC(hwnd);
	if (!deviceContext)
	{
		return false;
	}
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	HGLRC renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);

	ReleaseDC(hwnd, deviceContext);

	return true;
}

void GLDeviceResources::Release(HWND hwnd)
{
	if (m_renderingContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = nullptr;
	}

	if (m_deviceContext)
	{
		ReleaseDC(hwnd, m_deviceContext);
		m_deviceContext = nullptr;
	}
}

HDC GLDeviceResources::GetDeviceContext() const
{
	return m_deviceContext;
}

HGLRC GLDeviceResources::GetRenderingContext() const
{
	return m_renderingContext;
}

void GLDeviceResources::GetWorldMatrix(Matrix& matrix) const
{
	matrix = m_worldMatrix;
}

void GLDeviceResources::GetProjMatrix(Matrix& matrix) const
{
	matrix = m_projectionMatrix;
}

void GLDeviceResources::BuildPerspectiveFovLHMatrix(Matrix& matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth) const
{
	matrix.Identity();
	matrix.mat[0].x /= (screenAspect * tan(fieldOfView * 0.5f));
	matrix.mat[1].y /= tan(fieldOfView * 0.5f);
	matrix.mat[2].z = screenDepth / (screenDepth - screenNear);
	matrix.mat[3].z = (-screenNear * screenDepth) / (screenDepth - screenNear);
	matrix.mat[4].w = 0.0f;
}

bool GLDeviceResources::InitializeExt(HWND hwnd)
{
	HDC deviceContext = GetDC(hwnd);
	if (!deviceContext)
	{
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelFormat;
	int error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		return false;
	}

	HGLRC renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		return false;
	}

	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		return false;
	}

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);
	ReleaseDC(hwnd, deviceContext);

	return true;
}

bool GLDeviceResources::InitOpenGL(HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
{
	if (!InitializeExt(hwnd))
	{
		return false;
	}

	m_deviceContext = GetDC(hwnd);
	if (!m_deviceContext)
	{
		return false;
	}
	int attributeListInt[19];
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	attributeListInt[18] = 0;
	int pixelFormat[1];
	unsigned int formatCount;
	BOOL result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, nullptr, 1, pixelFormat, &formatCount);
	if (result != 1)
	{
		return false;
	}
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if (result != 1)
	{
		return false;
	}
	int attributeList[5];
	//5.0 version of OpenGL 
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 5;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;
	attributeList[4] = 0;

	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, nullptr, attributeList);
	result = wglMakeCurrent(m_deviceContext, m_renderingContext);
	if (result != 1)
	{
		return false;
	}

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	float fieldOfView = 3.14159265358979323846f / 4.0f;
	float screenAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

	BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	char *vendorString = (char*)glGetString(GL_VENDOR);
	char *rendererString = (char*)glGetString(GL_RENDERER);

	if (vsync)
	{
	result = wglSwapIntervalEXT(1);
	}
	else
	{
	result = wglSwapIntervalEXT(0);
	}

	if (result != 1)
	{
		return false;
	}

	return true;
}

#include "GLDevice.h"
#include <math.h>

GLDevice::GLDevice()
	: m_deviceContext(nullptr), m_renderingContext(nullptr), m_hWnd(nullptr), m_hInst(nullptr) { }

GLDevice::~GLDevice() { }

bool GLDevice::Init(HWND hwnd)
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
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stdout, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);

	ReleaseDC(hwnd, deviceContext);

	return true;
}

void GLDevice::Release(HWND hwnd)
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

HDC GLDevice::GetDeviceContext() const
{
	return m_deviceContext;
}

HGLRC GLDevice::GetRenderingContext() const
{
	return m_renderingContext;
}

bool GLDevice::InitializeExt(HWND hwnd)
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

	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);
	ReleaseDC(hwnd, deviceContext);

	return true;
}

bool GLDevice::InitOpenGL(HWND hwnd, const DisplayState &displayState)
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

	if (displayState.VsynEnabled)
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

#if _DEBUG
	if (glDebugMessageCallback){
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglCallbackFunction, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
	}
	else
	{
		std::cout << "glDebugMessageCallback not available" << std::endl;
	}
#endif

	return true;
}

#pragma once
#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/wglew.h>
#include "Matrix.h"
#include "Interfaces.h"
#include <iostream>

#pragma comment(lib, "glew32s.lib")

inline void APIENTRY openglCallbackFunction(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam){
	std::cout << "---------------------opengl-callback-start------------" << std::endl;
	std::cout << "message: " << message << std::endl;
	std::cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "OTHER";
		break;
	}
	std::cout << std::endl;

	std::cout << "id: " << id << std::endl;
	std::cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "HIGH";
		break;
	default: break;
	}
	std::cout << std::endl;
	std::cout << "---------------------opengl-callback-end--------------" << std::endl;
}

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

private:
	static bool InitializeExt(HWND hwnd);
	HDC m_deviceContext;
	HGLRC m_renderingContext;
	HWND m_hWnd;
	HINSTANCE m_hInst;

};
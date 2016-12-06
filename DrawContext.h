#pragma once

#include <windows.h>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Interfaces.h"
#include "Matrix.h"
#include "Util.h"

inline void PreGLCall(const char *name, void *funcptr, int len_args, ...)
{
	//Util::DebugPrintF("Calling: %s (%d arguments)\n", name, len_args);
}

inline void PostCallback(const char *name, void *funcptr, int len_args, ...) {
	GLenum error_code;
	error_code = glad_glGetError();

	if (error_code != GL_NO_ERROR)
	{
		Util::DebugPrintF("ERROR %d in %s\n", error_code, name);
	}
}

inline void DefaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Util::DebugPrintF("Pressed key: %i\n", key);
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default: break;
		}
	}
}

class DrawContext
{
public:
	DrawContext();
	~DrawContext();
	
	void BeginScene();
	void Draw() const;
	void EndScene() const;
	GLFWwindow* DrawContext::GetWindow() const;

	static const Color DefaultClearColor;

private:
	bool Init();

	DisplayState m_currentDisplayState;
	GLuint m_vaoId;

	Color m_clearColor;

	float m_clearDepth;
	GLFWwindow* m_window;

	Matrix m_worldMatrix;
	Matrix m_projectionMatrix;

};

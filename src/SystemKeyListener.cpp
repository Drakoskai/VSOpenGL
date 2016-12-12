#include "pch.h"
#include "SystemKeyListener.h"

SystemKeyListener::SystemKeyListener() { }

SystemKeyListener::~SystemKeyListener() { }

void SystemKeyListener::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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

void SystemKeyListener::Update(float deltaTime) { }

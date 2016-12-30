#include "pch.h"
#include "SystemKeyListener.h"

SystemKeyListener::SystemKeyListener() { }

SystemKeyListener::~SystemKeyListener() { }

bool isCursorGrabbed = false;
void SystemKeyListener::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_ENTER:
			if (!isCursorGrabbed)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				isCursorGrabbed = true;
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				isCursorGrabbed
				= false;
			}
			break;

		default: break;
		}
	}
}

void SystemKeyListener::Update(float deltaTime) { }

#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "../Util/Util.h"

namespace OpenGL
{
	inline void PreGLCall(const char *name, void *funcptr, int len_args, ...)
	{
		Util::DebugPrintF("Calling: %s (%d arguments)\n", name, len_args);
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
}

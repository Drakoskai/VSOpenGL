#pragma once

#include "OpenGL.h"
#include "../Interfaces.h"
#include "../Math3d/Matrix.h"

namespace OpenGL
{
	class GLDevice
	{
	public:
		GLDevice();
		~GLDevice();

		void BeginScene();
		void Draw() const;
		void EndScene() const;
		GLFWwindow* GLDevice::GetWindow() const;

	private:
		bool Init();

		DisplayState m_currentDisplayState;
		Math3d::Color m_clearColor;
		float m_clearDepth;

		GLFWwindow* m_window;
	};
}

#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>
#include "../InputHandler.h"

class CameraKeyListener : public KeyInputListner
{
public:
	CameraKeyListener(View::Camera* camera);
	~CameraKeyListener();

	void Update(float deltaTime) override;
	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode) override;

private:
	View::Camera* m_camera;

	bool m_forward;
	bool m_backward;
	bool m_upward;
	bool m_downward;
	bool m_left;
	bool m_right;
};

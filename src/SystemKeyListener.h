#pragma once

#include "InputHandler.h"

class SystemKeyListener : public KeyInputListner
{
public:
	SystemKeyListener();
	~SystemKeyListener();
	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode) override;
	void Update(float deltaTime) override;
};

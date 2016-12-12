#pragma once

#include <GLFW/glfw3.h>
#include "Util/SimpleTimer.h"
#include <vector>

class KeyInputListner
{
public:
	virtual ~KeyInputListner() { }
	virtual void OnKeyEvent(GLFWwindow*, int key, int scancode, int action, int mode) = 0;
	virtual void Update(float deltaTime) = 0;
};

class MouseInputListner
{
public:
	virtual ~MouseInputListner() { }
	virtual void OnMouseMoveEvent(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void Update(float deltaTime) = 0;
};

class InputDispatcher
{
public:
	InputDispatcher(SimpleTimer* timer);
	~InputDispatcher();

	void KeyEventDispatch(GLFWwindow* window, int key, int scancode, int action, int mode);
	void MouseMovementEventDispatch(GLFWwindow* window, double xpos, double ypos);
	void Update();
	void AddKeyInputListener(KeyInputListner* listener);
	void AddMouseInputListener(MouseInputListner* listener);
private:
	SimpleTimer* m_timer;
	std::vector<KeyInputListner*> m_KeyListeners;
	std::vector<MouseInputListner*> m_MouseListeners;
};

class InputHandler
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseMovementMoveCallback(GLFWwindow* window, double xpos, double ypos);

	InputHandler(SimpleTimer* timer);
	~InputHandler()	{ }

	void AddKeyInputListener(KeyInputListner* listener) const;
	void AddMouseInputListener(MouseInputListner* listener) const;

	void Update();
};


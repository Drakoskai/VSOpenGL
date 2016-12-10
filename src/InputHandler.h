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

class InputDispatcher
{
public:
	InputDispatcher(SimpleTimer* timer);
	~InputDispatcher();

	void KeyEventDispatch(GLFWwindow* window, int key, int scancode, int action, int mode);

	void Update();

	void AddKeyInputListener(KeyInputListner* listener);

private:
	SimpleTimer* m_timer;
	std::vector<KeyInputListner*> m_listeners;

};



class InputHandler
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	InputHandler(SimpleTimer* timer);
	~InputHandler()	{ }

	void AddKeyInputListener(KeyInputListner* listener) const;

	void Update();
};


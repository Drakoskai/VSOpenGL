#include "pch.h"
#include "InputHandler.h"

static InputDispatcher* Dispatcher;

InputDispatcher::InputDispatcher(SimpleTimer* timer): m_timer(timer) { }

InputDispatcher::~InputDispatcher() { }

void InputDispatcher::KeyEventDispatch(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	for (auto it(m_KeyListeners.begin()), ite(m_KeyListeners.end()); it != ite; ++it)
	{
		(*it)->OnKeyEvent(window, key, scancode, action, mode);
	}
}

void InputDispatcher::MouseMovementEventDispatch(GLFWwindow* window, double xpos, double ypos)
{
	for (auto it(m_MouseListeners.begin()), ite(m_MouseListeners.end()); it != ite; ++it)
	{
		(*it)->OnMouseMoveEvent(window, xpos, ypos);
	}
}

void InputDispatcher::Update()
{
	float deltaTime = m_timer->GetDeltaTime();
	for (auto it(m_KeyListeners.begin()), ite(m_KeyListeners.end()); it != ite; ++it)
	{
		(*it)->Update(deltaTime);
	}
	for (auto it(m_MouseListeners.begin()), ite(m_MouseListeners.end()); it != ite; ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void InputDispatcher::AddKeyInputListener(KeyInputListner* listener) { m_KeyListeners.push_back(listener);
}

void InputDispatcher::AddMouseInputListener(MouseInputListner* listener) { m_MouseListeners.push_back(listener); }

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (Dispatcher)
	{
		Dispatcher->KeyEventDispatch(window, key, scancode, action, mode);
	}
}

void InputHandler::MouseMovementMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (Dispatcher)
	{
		Dispatcher->MouseMovementEventDispatch(window, xpos, ypos);
	}
}

InputHandler::InputHandler(SimpleTimer* timer)
{
	Dispatcher = new InputDispatcher(timer);
}

void InputHandler::AddKeyInputListener(KeyInputListner* listener) const
{
	if (Dispatcher)
	{
		Dispatcher->AddKeyInputListener(listener);
	}
}

void InputHandler::AddMouseInputListener(MouseInputListner* listener) const
{
	if (Dispatcher)
	{
		Dispatcher->AddMouseInputListener(listener);
	}
}

void InputHandler::Update()
{
	if (Dispatcher)
	{
		Dispatcher->Update();
	}
}

#include "pch.h"
#include "InputHandler.h"

static InputDispatcher* Dispatcher;

InputDispatcher::InputDispatcher(SimpleTimer* timer): m_timer(timer) { }

InputDispatcher::~InputDispatcher() { }

void InputDispatcher::KeyEventDispatch(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	for (auto it(m_listeners.begin()), ite(m_listeners.end()); it != ite; ++it)
	{
		float deltaTime = m_timer->GetDeltaTime();
		(*it)->OnKeyEvent(window, key, scancode, action, mode);
	}
}

void InputDispatcher::Update()
{
	float deltaTime = m_timer->GetDeltaTime();
	for (auto it(m_listeners.begin()), ite(m_listeners.end()); it != ite; ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void InputDispatcher::AddKeyInputListener(KeyInputListner* listener)
{
	m_listeners.push_back(listener);
}

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (Dispatcher)
	{
		Dispatcher->KeyEventDispatch(window, key, scancode, action, mode);
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

void InputHandler::Update()
{
	if (Dispatcher)
	{
		Dispatcher->Update();
	}
}

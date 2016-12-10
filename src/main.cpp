#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Util/SimpleTimer.h"
#include "View/Camera.h"
#include <memory>

//TODO: Move input classes/interfaces into their own files
class KeyInputListner
{
public:
	virtual ~KeyInputListner() { }
	virtual void OnKeyEvent(GLFWwindow*, int key, int scancode, int action, int mode) = 0;
	virtual void Update(float deltaTime) = 0;
};

class SystemKeyListener : public KeyInputListner
{
public:
	SystemKeyListener() { }
	~SystemKeyListener() { }
	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode) override
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
	void Update(float deltaTime) override { }
};

class CameraKeyListener : public KeyInputListner
{
public:
	CameraKeyListener(View::Camera* camera)
		: m_camera(camera), m_forward(false), m_backward(false), m_upward(false), m_downward(false),
		m_left(false), m_right(false), m_forwardSpeed(0), m_backwardSpeed(0), m_upwardSpeed(0),
		m_downwardSpeed(0), m_leftStrafeSpeed(0), m_rightStrafeSpeed(0)	{ }

	~CameraKeyListener() { }

	void Update(float deltaTime) override
	{
		if (m_right)
		{
			m_rightStrafeSpeed += deltaTime * 1.0f;

			if (m_rightStrafeSpeed > (deltaTime * 50.0f))
			{
				m_rightStrafeSpeed = deltaTime * 50.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_rightStrafeSpeed -= deltaTime * 0.5f;

			if (m_rightStrafeSpeed < 0.0f)
			{
				m_rightStrafeSpeed = 0.0f;
			}
		}
		if (m_left)
		{
			m_leftStrafeSpeed += deltaTime * 1.0f;

			if (m_leftStrafeSpeed > (deltaTime * 50.0f))
			{
				m_leftStrafeSpeed = deltaTime * 50.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_leftStrafeSpeed -= deltaTime* 0.5;

			if (m_leftStrafeSpeed < 0.0f)
			{
				m_leftStrafeSpeed = 0.0f;
			}	
		}
		if (m_forward)
		{
			m_forwardSpeed += deltaTime * 1.0f;
			if (m_forwardSpeed > (deltaTime * 50.0f))
			{
				m_forwardSpeed = deltaTime * 50.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_forwardSpeed -= deltaTime * 0.5f;

			if (m_forwardSpeed < 0.0f)
			{
				m_forwardSpeed = 0.0f;
			}
		}
		if (m_backward)
		{
			m_backwardSpeed += deltaTime * 1.0f;

			if (m_backwardSpeed > (deltaTime * 50.0f))
			{
				m_backwardSpeed = deltaTime * 50.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_backwardSpeed -= deltaTime * 0.5f;

			if (m_backwardSpeed < 0.0f)
			{
				m_backwardSpeed = 0.0f;
			}
		}
		if (m_upward)
		{
			m_upwardSpeed += deltaTime * 1.5f;

			if (m_upwardSpeed > (deltaTime * 15.0f))
			{
				m_upwardSpeed = deltaTime * 15.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_upwardSpeed -= deltaTime * 0.5f;

			if (m_upwardSpeed < 0.0f)
			{
				m_upwardSpeed = 0.0f;
			}
		}
		if (m_downward)
		{
			m_downwardSpeed += deltaTime * 1.5f;

			if (m_downwardSpeed > (deltaTime * 15.0f))
			{
				m_downwardSpeed = deltaTime * 15.0f;
			}
			OutputSpeed();
		}
		else
		{
			m_downwardSpeed -= deltaTime * 0.5f;

			if (m_downwardSpeed < 0.0f)
			{
				m_downwardSpeed = 0.0f;
			}
		}
		//TODO: Transform camera postion and rotation by speeds
	}

	void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mode) override
	{
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_D:
				m_right = true;
				break;
			case GLFW_KEY_A:
				m_left = true;
				break;
			case GLFW_KEY_W:
				m_forward = true;
				break;
			case GLFW_KEY_S:
				m_backward = true;
				break;
			case GLFW_KEY_SPACE:
				m_upward = true;
				break;
			case GLFW_KEY_Z:
				m_downward = true;
				break;
			default: break;
			}
	}
		if (action == GLFW_RELEASE)
		{
			switch (key)
			{
			case GLFW_KEY_D:
				m_right = false;
				break;
			case GLFW_KEY_A:
				m_left = false;
				break;
			case GLFW_KEY_W:
				m_forward = false;
				break;
			case GLFW_KEY_S:
				m_backward = false;
				break;
			case GLFW_KEY_SPACE:
				m_upward = false;
				break;
			case GLFW_KEY_Z:
				m_downward = false;
				break;
			default: break;
			}
		}
	}

private:
	void OutputSpeed() const
	{
		Util::DebugPrintF("Forward Speed: %f\n", m_forwardSpeed);
		Util::DebugPrintF("Backward Speed: %f\n", m_backwardSpeed);
		Util::DebugPrintF("Downward Speed: %f\n", m_downwardSpeed);
		Util::DebugPrintF("Upward Speed: %f\n", m_upwardSpeed);
		Util::DebugPrintF("Left Strafe Speed: %f\n", m_leftStrafeSpeed);
		Util::DebugPrintF("Right Strafe Speed: %f\n", m_rightStrafeSpeed);
	}

	View::Camera* m_camera;

	bool m_forward;
	bool m_backward;
	bool m_upward;
	bool m_downward;
	bool m_left;
	bool m_right;

	float m_forwardSpeed;
	float m_backwardSpeed;
	float m_upwardSpeed;
	float m_downwardSpeed;
	float m_leftStrafeSpeed;
	float m_rightStrafeSpeed;
};

class InputDispatcher
{
public:
	InputDispatcher(SimpleTimer* timer) : m_timer(timer) { }
	~InputDispatcher() { }

	void KeyEventDispatch(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		for (auto it(m_listeners.begin()), ite(m_listeners.end()); it != ite; ++it)
		{
			float deltaTime = m_timer->GetDeltaTime();
			(*it)->OnKeyEvent(window, key, scancode, action, mode);
		}
	}

	void Update()
	{
		float deltaTime = m_timer->GetDeltaTime();
		for (auto it(m_listeners.begin()), ite(m_listeners.end()); it != ite; ++it)
		{		
			(*it)->Update(deltaTime);
		}
	}

	void AddKeyInputListener(KeyInputListner* listener)
	{
		m_listeners.push_back(listener);
	}

private:
	SimpleTimer* m_timer;
	std::vector<KeyInputListner*> m_listeners;

};
static InputDispatcher* Dispatcher;

class InputHandler
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (Dispatcher)
		{
			Dispatcher->KeyEventDispatch(window, key, scancode, action, mode);
		}
	}

	InputHandler(SimpleTimer* timer) { Dispatcher = new InputDispatcher(timer); }
	~InputHandler()	{ }

	void AddKeyInputListener(KeyInputListner* listener) const
	{
		if (Dispatcher)
		{
			Dispatcher->AddKeyInputListener(listener);
		}
	}

	void Update()
	{
		if (Dispatcher)
		{
			Dispatcher->Update();
		}
	}
};

int main(int, char**)
{
	using namespace OpenGL;
	using namespace Model;
	using namespace Math3d;

	GLDevice* device = new GLDevice();
	GLFWwindow* window = device->GetWindow();
	SimpleTimer* timer = new SimpleTimer();
	InputHandler input = InputHandler(timer);

	glfwSetKeyCallback(window, InputHandler::KeyCallback);

	SystemKeyListener systemListener = SystemKeyListener();
	input.AddKeyInputListener(&systemListener);

	View::Camera* camera = new View::Camera();
	camera->SetPosition(0, 0, -3);

	CameraKeyListener cameraListener = CameraKeyListener(camera);
	input.AddKeyInputListener(&cameraListener);

	Object* teapot = new Object("Assets/Meshes/teapot.obj");
	teapot->GetTransform()
		.SetScale(0.8f)
		.Translate(-4, 0, 0)
		.RotateX(15.0f);

	Object* cube = new Object("Assets/Meshes/cube.obj");
	cube->GetTransform()
		.Translate(3, 2, 0)
		.RotateX(15.0f);

	timer->Start();
	float smooth = 1.0f;
	while (!glfwWindowShouldClose(window))
	{
		timer->Update();
		input.Update();
		camera->Update();
		
		Matrix viewProj = camera->GetView() * camera->GetProj();

		teapot->GetTransform()
			.RotateY(smooth * 20 * timer->GetDeltaTime());

		cube->GetTransform()
			.RotateY(smooth * 20 * timer->GetDeltaTime());

		cube->Update(viewProj);
		teapot->Update(viewProj);

		device->BeginScene();

		teapot->Draw();
		cube->Draw();

		device->EndScene();
	}

	timer->End();

	SafeDelete(cube);
	SafeDelete(teapot);
	SafeDelete(camera);
	SafeDelete(timer);
	SafeDelete(device);

	return 0;
}

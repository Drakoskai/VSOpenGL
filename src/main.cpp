#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Util/SimpleTimer.h"
#include "View/Camera.h"
#include "InputHandler.h"
#include "View/CameraKeyInputListener.h"
#include "View/CameraMouseInputListener.h"
#include <functional>

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

class Scene
{
public:
	Scene(OpenGL::GLDevice& device, SimpleTimer& timer, InputHandler& input)
		: m_device(device), m_timer(timer), m_input(input) { }

	~Scene() { }

	Model::Object& AddObjectToScene(const char* filename)
	{
		Model::Object* obj = new Model::Object(filename);
		m_objects.push_back(obj);

		return *obj;
	}

	void Frame()
	{
		m_device.BeginScene();

		for (auto&& drawable : m_objects) { drawable->Draw(); }

		m_device.EndScene();
	}

private:
	OpenGL::GLDevice& m_device;
	SimpleTimer& m_timer;
	InputHandler& m_input;
	std::vector<Model::Object*> m_objects;

};

int main(int, char**)
{
	using namespace OpenGL;
	using namespace Model;
	using namespace Math3d;

	GLDevice* device = new GLDevice();

	SimpleTimer* timer = new SimpleTimer();

	InputHandler* input = new InputHandler(timer);

	glfwSetKeyCallback(device->GetWindow(), InputHandler::KeyCallback);
	glfwSetCursorPosCallback(device->GetWindow(), InputHandler::MouseMovementMoveCallback);

	SystemKeyListener systemListener = SystemKeyListener();

	input->AddKeyInputListener(&systemListener);

	View::Camera camera = View::Camera();
	camera.GetTransform()
		.SetPosition(0, 0, -3);

	CameraKeyListener cameraKeyListener = CameraKeyListener(&camera);
	CameraMouseInputListener cameraMouseListener = CameraMouseInputListener(&camera);

	input->AddKeyInputListener(&cameraKeyListener);
	input->AddMouseInputListener(&cameraMouseListener);

	Scene scene = Scene(*device, *timer, *input);

	Object& teapot = scene.AddObjectToScene("Assets/Meshes/teapot.obj");

	teapot.GetTransform()
		.SetScale(0.8f)
		.Translate(-4, 0, 0)
		.RotateX(15.0f);

	Object& cube = scene.AddObjectToScene("Assets/Meshes/cube.obj");

	cube.GetTransform()
		.Translate(3, 2, 0)
		.RotateX(12.0f);

	float smooth = 1.0f;

	std::vector<std::function<void()>> workflows;

	auto teapotAnimation = [&]()
	{
		teapot.GetTransform()
			.RotateY(smooth * 20 * timer->GetDeltaTime());
	};

	workflows.push_back(teapotAnimation);

	auto cubeAnimation = [&]()
	{
		cube.GetTransform()
			.RotateY(smooth * -14 * timer->GetDeltaTime());
	};

	workflows.push_back(cubeAnimation);

	timer->Start();

	while (!glfwWindowShouldClose(device->GetWindow()))
	{
		timer->Update();
		input->Update();
		camera.Update();

		for (auto && workflow : workflows) { workflow(); }

		Matrix viewProj = camera.GetView() * camera.GetProj();

		teapot.Update(viewProj);
		cube.Update(viewProj);

		scene.Frame();
	}

	timer->End();

	SafeDelete(input);
	SafeDelete(timer);
	SafeDelete(device);

	return 0;
}

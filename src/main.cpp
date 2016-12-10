#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Util/SimpleTimer.h"
#include "View/Camera.h"
#include "InputHandler.h"
#include "View/CameraKeyInputListener.h"

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
	camera->GetTransform()
		.SetPosition(0, 0, -3);

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
		.RotateX(12.0f);

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
			.RotateY(smooth * -14 * timer->GetDeltaTime());

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

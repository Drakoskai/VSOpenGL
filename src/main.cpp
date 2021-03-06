#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Util/SimpleTimer.h"
#include "View/Camera.h"
#include "InputHandler.h"
#include "View/CameraKeyInputListener.h"
#include "View/CameraMouseInputListener.h"
#include "SystemKeyListener.h"
#include "Scene.h"

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
	camera
		.SetPosition(2.47737f, -1.05385f, -77.5735f);

	CameraKeyListener cameraKeyListener = CameraKeyListener(&camera);
	CameraMouseInputListener cameraMouseListener = CameraMouseInputListener(&camera);

	input->AddKeyInputListener(&cameraKeyListener);
	input->AddMouseInputListener(&cameraMouseListener);

	Scene scene = Scene(*device, *timer, *input);

	Object& teapot = scene.AddObjectToScene("Assets/Meshes/teapot.obj");

	teapot.GetTransform()
		.Translate(-2, 10, 0);

	float smooth = 1.0f;

	std::vector<std::function<void()>> workflows;

	auto teapotAnimation = [&]()
	{
		teapot.GetTransform()
			.RotateY(smooth * 20 * timer->GetDeltaTime());
	};

	workflows.push_back(teapotAnimation);

	timer->Start();

	while (!glfwWindowShouldClose(device->GetWindow()))
	{
		timer->Update();
		input->Update();
		camera.Update();

		for (auto&& workflow : workflows) { workflow(); }
		teapot.Update(camera.GetView(), camera.GetProj(), camera.GetPosition());
		scene.Frame();
	}

	timer->End();

	SafeDelete(input);
	SafeDelete(timer);
	SafeDelete(device);

	return 0;
}

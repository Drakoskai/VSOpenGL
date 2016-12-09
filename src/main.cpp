#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Util/SimpleTimer.h"
#include "View/Camera.h"

int main(int, char**)
{
	using namespace OpenGL;
	using namespace Model;
	using namespace Math3d;

	GLDevice* device = new GLDevice();
	GLFWwindow* window = device->GetWindow();
	SimpleTimer timer = SimpleTimer();

	View::Camera camera = View::Camera();
	camera.SetPosition(0, 0, -3);

	Object teapot = Object("Assets/Meshes/teapot.obj");
	teapot.GetTransform()
		.SetScale(0.8f)
		.Translate(-4, 0, 0)
		.RotateX(15.0f);

	Object cube = Object("Assets/Meshes/cube.obj");
	cube.GetTransform()
		.Translate(3, 2, 0)
		.RotateX(15.0f);

	float smooth = 1.0f;

	timer.Start();

	while (!glfwWindowShouldClose(window))
	{
		timer.Update();
		camera.Update();

		teapot.GetTransform()
			.RotateY(smooth * 20 * timer.GetDeltaTime());

		cube.GetTransform()
			.RotateY(smooth * 20 * timer.GetDeltaTime());

		Matrix viewProj = camera.GetView() * camera.GetProj();
		
		cube.Update(viewProj);
		teapot.Update(viewProj);

		device->BeginScene();

		teapot.Draw();
		cube.Draw();

		device->EndScene();
	}

	timer.End();
	SafeDelete(device);

	return 0;
}

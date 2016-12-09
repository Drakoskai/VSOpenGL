#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"
#include "Math3d/Angle.h"
#include "Util/SimpleTimer.h"

class PerspectiveCamera
{
public:
	PerspectiveCamera()
	{
		using namespace Math3d;
		m_position = -Vector4f::UnitZ;
		m_position += Vector4f(0, 0, -4);
		m_fieldOfView = Angle::FromDegrees(View::DefaultFieldOfView);
		m_projection = MakePerspective(m_fieldOfView, View::DefaultWidth, View::DefaultHeight, View::DefaultScreenNear, View::DefaultScreenDepth);
	}

	~PerspectiveCamera() { }

	void Update()
	{
		using namespace Math3d;

		Vector4f focus = m_position + Vector4f::UnitZ;
		Vector4f up = Vector4f::UnitY;
		m_view = MakeLookAt(m_position, focus, up);
	}

	Math3d::Angle m_fieldOfView;

	Math3d::Vector4f m_position;
	Math3d::Matrix m_view;
	Math3d::Matrix m_projection;
};

int main(int, char**)
{
	using namespace OpenGL;
	using namespace Model;
	using namespace Math3d;

	GLDevice* device = new GLDevice();
	GLFWwindow* window = device->GetWindow();
	SimpleTimer timer = SimpleTimer();

	PerspectiveCamera camera = PerspectiveCamera();

	Object object = Object("Assets/Meshes/teapot.obj");

	Angle initXRot = Angle::FromDegrees(15.0f);

	object.GetTransform()
		//.Scale(0.3f)
		//.Translate(0, 0, 5)
		.RotateX(15.0f);

	float smooth = 1.0f;

	timer.Start();

	while (!glfwWindowShouldClose(window))
	{
		timer.Update();
		camera.Update();

		object.GetTransform()
			.RotateY(smooth * 20 * timer.GetDeltaTime());
		Matrix model;
		Matrix mvp = camera.m_projection * camera.m_view * model;
		object.Update(mvp);

		device->BeginScene();

		object.Draw();

		device->EndScene();
	}

	timer.End();
	SafeDelete(device);

	return 0;
}

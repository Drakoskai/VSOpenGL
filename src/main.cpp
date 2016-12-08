#include "pch.h"
#include "GL/GLDevice.h"
#include "Model/Object.h"

int main(int, char **)
{
	using namespace OpenGL;
	using namespace Model;
	using namespace Math3d;

	GLDevice* device = new GLDevice();
	GLFWwindow* window = device->GetWindow();

	Object object = Object("Assets/Meshes/teapot.obj");

	int width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);

	float aspect = float(width) / float(height);
	
	object.GetTransform()
		.Scale(0.3f)
		.RotateX(15.0f);
	//.Translate(Vector3f(0,0,3));
	
	
	Transform cameraTransform;
	Matrix view = MakeLookAt(Vector3f::Zero, Vector3f::Forward, Vector3f::Up);
	Matrix model = MakeTranslate(Vector3f(0,0,-1));
	Matrix projection = MakePerspective(75.0f, aspect, .001f, 1000.0f);

	while (!glfwWindowShouldClose(window))
	{	
		Matrix world = model * projection;// *view;// ;
		
		object.GetTransform()
		.RotateY(1.0f);
		
		object.Update(world);

		device->BeginScene();

		object.Draw();

		device->EndScene();
	}

	SafeDelete(device);

	return 0;
}

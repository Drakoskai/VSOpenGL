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

	//glfwSetKeyCallback(window, OnKey);

	int width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);

	float aspect = GLfloat(width) / height;
	object.GetTransform().Scale(Vector3f(.3f,.3f,.3f));
	while (!glfwWindowShouldClose(window))
	{
		Matrix projection = MakePerspective(60.0f, aspect, 0.1f, 1000.0f);
		object.GetTransform().RotateY(1.0f);
		object.Update(projection);

		device->BeginScene();

		object.Draw();

		device->EndScene();
	}

	delete device;

	return 0;
}

/*void OnKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
if (action == GLFW_PRESS)
{
switch (key)
{
case GLFW_KEY_ESCAPE:
glfwSetWindowShouldClose(window, GL_TRUE);
break;

case GLFW_KEY_K:
Inner--;
if (Inner < 1.0)  Inner = 1.0;
glUniform1f(InnerLoc, Inner);
break;

case GLFW_KEY_I:
Inner++;
if (Inner > 64)  Inner = 64.0;
glUniform1f(InnerLoc, Inner);
break;

case GLFW_KEY_L:
Outer--;
if (Outer < 1.0)  Outer = 1.0;
glUniform1f(OuterLoc, Outer);
break;

case GLFW_KEY_O:
Outer++;
if (Outer > 64)  Outer = 64.0;
glUniform1f(OuterLoc, Outer);
break;

case GLFW_KEY_R:
Inner = 1.0;
Outer = 1.0;
glUniform1f(InnerLoc, Inner);
glUniform1f(OuterLoc, Outer);
break;

case GLFW_KEY_M: {
static GLenum glmode = GL_LINE;
glmode = (glmode == GL_FILL ? GL_LINE : GL_FILL);
glPolygonMode(GL_FRONT_AND_BACK, glmode);
} break;
default: break;
}
}
}*/

#include <stdio.h>
#include <stdlib.h>
#include "DrawContext.h"
#include "Model.h"

int main(int, char **)
{
	DrawContext* dc = new DrawContext();

	if (!dc->Init())
	{
		Util::DebugPrintF("Failed to initalize renderer.\n");
		delete dc;
		return -1;
	}

	GLFWwindow* window = dc->GetWindow();

	Model m = Model("Assets/Meshes/teapot.obj");
	m.Init();
	glClearColor(0.0, 0.0, 0.0, 1.0);

	//glfwSetKeyCallback(window, OnKey);

	int width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);

	float aspect = GLfloat(width) / height;
	m.GetTransform().Scale(Vector3f(.3f,.3f,.3f));
	while (!glfwWindowShouldClose(window))
	{
		Matrix projection = MakePerspective(60.0f, aspect, 0.1f, 1000.0f);
		m.GetTransform().RotateY(1.0f);
		m.Update(projection);

		dc->BeginScene();

		m.Draw();

		dc->EndScene();
	}

	delete dc;

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

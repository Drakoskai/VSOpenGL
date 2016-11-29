#include <stdio.h>
#include <stdlib.h>
#include "DrawContext.h"
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "Teapot.h"

GLfloat  Inner = 10.0f;
GLfloat  Outer = 10.0f;

GLuint InnerLoc;
GLuint OuterLoc;

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mode);

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

	enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };

	GLuint buffers[NumVertexBuffers];

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(NumVertexBuffers, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TeapotVertices), TeapotVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[ElementBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TeapotIndices), TeapotIndices, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "teapot.vert" },
		{ GL_TESS_CONTROL_SHADER, "teapot.cont" },
		{ GL_TESS_EVALUATION_SHADER, "teapot.eval" },
		{ GL_FRAGMENT_SHADER, "teapot.frag" },
		{ GL_NONE, nullptr }
	};

	GLuint program;
	GLint vPosition;
	GLuint PLoc;
	GLint mv;

	program = dc->LoadShader(shaders);
	glUseProgram(program);

	vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));

	PLoc = glGetUniformLocation(program, "P");
	mv = glGetUniformLocation(program, "MV");

	InnerLoc = glGetUniformLocation(program, "Inner");
	OuterLoc = glGetUniformLocation(program, "Outer");

	glUniform1f(InnerLoc, Inner);
	glUniform1f(OuterLoc, Outer);

	Transform trans = Transform();
	trans.Translate(Vector3f(-0.2625f, -1.575f, -1.0f));
	trans.Translate(Vector3f(0.0f, 0.0f, -7.5f));

	glUniformMatrix4fv(mv, 1, GL_TRUE, trans.GetModelView());
	glPatchParameteri(GL_PATCH_VERTICES, NumTeapotVerticesPerPatch);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	int width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);

	float aspect = GLfloat(width) / height;

	glfwSetKeyCallback(window, OnKey);

	/*float ** vertices = new float*[NumTeapotVertices];
	for (int i = 0; i < NumTeapotVertices; i++)
	{
		vertices[i] = new float[3];
		for (int j = 0; j < 3; j++)
		{
			vertices[i][j] = TeapotVertices[i][j];
		}
	}

	GLint *** elements = new GLint**[NumTeapotIndices];
	for (int i = 0; i < NumTeapotIndices; i++)
	{
		GLint ** temp = new GLint*[4];
		for (int j = 0; j < NumTeapotIndices; j++)
		{
			temp[j] = new GLint[4];
			for (int k = 0; k < 4; k++)
			{
				temp[j][k] = TeapotIndices[i][j][k];
			}
		}
		elements[i] = temp;
	}*/


	//Model m = Model(vertices, NumTeapotVertices, elements, NumTeapotIndices, NumTeapotVerticesPerPatch);

	//m.Init(*dc);
	//Transform t = m.GetTransform();
	//t.Translate(Vector3f(-0.2625f, -1.575f, -1.0f));
	//t.Translate(Vector3f(0.0f, 0.0f, -7.5f));

	while (!glfwWindowShouldClose(window))
	{
		Matrix projection = MakePerspective(60.0, aspect, 5, 10);
		//m.Update(projection);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//m.Draw();
		trans.RotateY(static_cast<float>(glfwGetTime()));

		trans.Update();

		glUniformMatrix4fv(mv, 1, GL_TRUE, trans.GetModelView());

		glUniformMatrix4fv(PLoc, 1, GL_TRUE, projection);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_PATCHES, NumTeapotVertices, GL_UNSIGNED_INT, static_cast<void*>(nullptr));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete dc;

	return 0;
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mode)
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
}

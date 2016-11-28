#include <stdio.h>
#include <stdlib.h>
#include "GLDrawContext.h"
#include <iostream>
#include "Model.h"
#include "Vertex.h"
#include "Camera.h"

static const struct VertexP2C vertices[3] =
{
	{ Vector2f(-0.6f, -0.4f), Color(1.f, 0.f, 0.f) },
	{ Vector2f(0.6f, -0.4f), Color(0.0f, 1.0f, 0.0f) },
	{ Vector2f(0.f, 0.6f), Color(0.f, 0.f, 1.f) }
};

int main(int, char **)
{
	GLDrawContext* dc = new GLDrawContext();

	if (!dc->Init())
	{
		Util::DebugPrintF("Failed to initalize renderer.\n");
		delete dc;
		return -1;
	}

	GLuint vertex_buffer;
	GLuint program;
	GLint mvp_location;
	GLint vpos_location;
	GLint vcol_location;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	program = dc->LoadShaderProgramFromFile("test");

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, static_cast<void*>(nullptr));

	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 2));

	GLFWwindow* window = dc->GetWindow();

	CameraSimpleOrtho camera = CameraSimpleOrtho();
	ViewProps viewProps= {};
	while (!glfwWindowShouldClose(window))
	{
		int width;
		int height;

		glfwGetFramebufferSize(window, &width, &height);
			
		viewProps.height = height;
		viewProps.width = width;
		glViewport(0, 0, width, height);
		camera.Update(viewProps);
		Matrix modelViewPerspective = camera.GetModelView();

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);

		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(modelViewPerspective.mat));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	delete dc;

	return 0;
}

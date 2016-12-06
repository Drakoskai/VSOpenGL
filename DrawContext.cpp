#include "pch.h"
#include "DrawContext.h"
#include "Util.h"

const Color DrawContext::DefaultClearColor = Colors::Black;

DrawContext::DrawContext()
	: m_vaoId(0), m_clearDepth(0), m_window(nullptr)
{
	m_clearColor = DefaultClearColor;
	m_clearDepth = 1.0f;
	assert(Init());
}

DrawContext::~DrawContext()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}

	glfwTerminate();
}

bool DrawContext::Init()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(800, 600, "", nullptr, nullptr);

	glfwMakeContextCurrent(m_window);
	if (!m_window)
	{
		Util::DebugPrintF("Failed to create GLFW window\n");

		return false;
	}

	glfwSwapInterval(1);

	glfwSetKeyCallback(m_window, DefaultKeyCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		Util::DebugPrintF("OpenGL failed to intialize.\n");
		return false;
	}

	if (Util::IsDebug)
	{
		glad_set_pre_callback(PreGLCall);
		glad_set_post_callback(PostCallback);
		glad_debug_glClear = glad_glClear;
	}


	Util::DebugPrintF("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
	if (GLVersion.major < 2) {
		Util::DebugPrintF("Your system doesn't support OpenGL >= 2!\n");
		return false;
	}

	Util::DebugPrintF("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	return true;
}

void DrawContext::BeginScene()
{
	glClearBufferfv(GL_COLOR, 0, m_clearColor);
	glClearBufferfv(GL_DEPTH, 0, &m_clearDepth);
}

void DrawContext::Draw() const { }

void DrawContext::EndScene() const
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
GLFWwindow* DrawContext::GetWindow() const
{
	return m_window;
}

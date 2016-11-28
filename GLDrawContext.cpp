#include "GLDrawContext.h"
#include <fstream>
#include "Util.h"

GLDrawContext::GLDrawContext()
	: m_vaoId(0), m_clearDepth(0), m_window(nullptr)
{
	m_clearColor[0] = 0.0f;
	m_clearColor[1] = 0.0f;
	m_clearColor[2] = 0.0f;
	m_clearColor[3] = 0.0f;
}

GLDrawContext::~GLDrawContext()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}

	glfwTerminate();
}

bool GLDrawContext::Init()
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

#ifdef GLAD_DEBUG	
	glad_set_pre_callback(PreGLCall);
	glad_set_post_callback(PostCallback);
	glad_debug_glClear = glad_glClear;
#endif
	Util::DebugPrintF("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
	if (GLVersion.major < 2) {
		Util::DebugPrintF("Your system doesn't support OpenGL >= 2!\n");
		return false;
	}

	Util::DebugPrintF("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	return true;

}

void GLDrawContext::BeginScene() { }

void GLDrawContext::Draw() const { }

void GLDrawContext::EndScene() const { }

void GLDrawContext::Release() const
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
	}

	glfwTerminate();
}

GLFWwindow* GLDrawContext::GetWindow() const
{
	return m_window;
}

GLuint GLDrawContext::LoadShader(const char* text, GLenum type) const
{
	GLuint shader;
	GLint shader_ok;
	GLsizei log_length;
	char info_log[8192];

	shader = glCreateShader(type);
	if (shader != 0)
	{
		glShaderSource(shader, 1, (const GLchar**)&text, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
		if (shader_ok != GL_TRUE)
		{
			Util::DebugPrintF("ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex");
			glGetShaderInfoLog(shader, 8192, &log_length, info_log);
			Util::DebugPrintF("ERROR: \n%s\n\n", info_log);
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}

GLuint GLDrawContext::LoadShaderProgram(const char* vs_text, const char* fs_text) const
{
	GLuint program = 0u;
	GLint program_ok;
	GLuint vertex_shader = 0u;
	GLuint fragment_shader = 0u;
	GLsizei log_length;
	char info_log[8192];

	vertex_shader = LoadShader(vs_text, GL_VERTEX_SHADER);
	if (vertex_shader != 0u)
	{
		fragment_shader = LoadShader(fs_text, GL_FRAGMENT_SHADER);
		if (fragment_shader != 0u)
		{
			/* make the program that connect the two shader and link it */
			program = glCreateProgram();
			if (program != 0u)
			{
				/* attach both shader and link */
				glAttachShader(program, vertex_shader);
				glAttachShader(program, fragment_shader);
				glLinkProgram(program);
				glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

				if (program_ok != GL_TRUE)
				{
					fprintf(stderr, "ERROR, failed to link shader program\n");
					glGetProgramInfoLog(program, 8192, &log_length, info_log);
					fprintf(stderr, "ERROR: \n%s\n\n", info_log);
					glDeleteProgram(program);
					glDeleteShader(fragment_shader);
					glDeleteShader(vertex_shader);
					program = 0u;
				}
			}
		}
		else
		{
			fprintf(stderr, "ERROR: Unable to load fragment shader\n");
			glDeleteShader(vertex_shader);
		}
	}
	else
	{
		fprintf(stderr, "ERROR: Unable to load vertex shader\n");
	}
	return program;
}

std::string GLDrawContext::LoadShaderFromFile(const char* filename) const
{
	std::ifstream ifile(filename);
	std::string outstr;
	getline(ifile, outstr, '\0');

	return outstr;
}

GLuint GLDrawContext::LoadShaderProgramFromFile(const char* filename) const
{
	std::string vertFilename = filename;
	vertFilename += ".vert";
	std::string fragFilename = filename;
	fragFilename += ".frag";
	std::string vertText = LoadShaderFromFile(vertFilename.c_str());
	std::string fragText = LoadShaderFromFile(fragFilename.c_str());

	return LoadShaderProgram(vertText.c_str(), fragText.c_str());
}

#include "../pch.h"
#include "Shader.h"
#include "../Util/Util.h"

namespace OpenGL
{
	Shader::Shader(std::vector<ShaderInfo> shaders)
		: m_shaderProg(0), m_uniformMVP(0), m_numShaders(0), m_shaderInfo(shaders)
	{
		m_shaderProg = LoadShaders(&shaders[0]);
		assert(m_shaderProg != 0);
	}

	Shader::~Shader()
	{
		m_uniformMVP = 0;
		if (m_shaderProg != 0)
		{		
			glDeleteProgram(m_shaderProg);
			m_shaderProg = 0;
		}
	}

	void Shader::Set() const { glUseProgram(m_shaderProg); }

	void Shader::Unset() { glUseProgram(0); }

	GLuint Shader::LoadShader(const char* text, GLenum type)
	{
		using namespace Util;
		GLuint shader;
		GLint shader_ok;
		GLsizei log_length;
		char info_log[8192];

		shader = glCreateShader(type);
		if (shader != 0)
		{
			glShaderSource(shader, 1, static_cast<const GLchar**>(&text), nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
			if (shader_ok != GL_TRUE)
			{
				DebugPrintF("ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex");
				glGetShaderInfoLog(shader, 8192, &log_length, info_log);
				DebugPrintF("ERROR: \n%s\n\n", info_log);
				glDeleteShader(shader);
				shader = 0;
			}
		}

		return shader;
	}

	std::string Shader::LoadShaderFromFile(const char* filename) const
	{
		std::ifstream ifile(filename);
		std::string outstr;
		getline(ifile, outstr, '\0');

		return outstr;
	}

	GLuint Shader::LoadShaders(ShaderInfo* shaders) const
	{
		using namespace Util;
		if (shaders == nullptr)
		{
			return 0;
		}

		GLuint program = glCreateProgram();

		ShaderInfo* entry = shaders;
		while (entry->type != GL_NONE)
		{
			GLuint shader = glCreateShader(entry->type);

			entry->shader = shader;

			std::string src = LoadShaderFromFile(entry->filename);

			if (src.length() == 0)
			{
				for (entry = shaders; entry->type != GL_NONE; ++entry)
				{
					glDeleteShader(entry->shader);
					entry->shader = 0;
				}

				return 0;
			}
			const char* source = src.c_str();
			glShaderSource(shader, 1, &source, nullptr);

			glCompileShader(shader);

			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				GLsizei len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

				GLchar* log = new GLchar[len + 1];
				glGetShaderInfoLog(shader, len, &len, log);
				DebugPrintF("Shader compilation failed: %s\n", log);
				SafeDeleteArr(log);

				return 0;
			}

			glAttachShader(program, shader);
			++entry;
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			DebugPrintF("Shader linking failed: %s\n", log);
			SafeDeleteArr(log);

			for (entry = shaders; entry->type != GL_NONE; ++entry)
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			for (uint32_t i = 0; i < m_numShaders; i++)
			{
				GLuint shaderId = m_shaderInfo[i].shader;
				if (m_shaderInfo[i].type != GL_NONE && shaderId != 0)
				{
					glDetachShader(m_shaderProg, shaderId);
					glDeleteShader(shaderId);
				}
			}
			return 0;
		}

		return program;
	}
}

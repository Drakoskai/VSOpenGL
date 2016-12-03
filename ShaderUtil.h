#pragma once

#include "glad.h"
#include "DrawContext.h"
#include <string>
#include <fstream>

struct ShaderInfo
{
	GLenum type;
	const char* filename;
	GLuint shader;
};

namespace Util
{
	

	inline GLuint LoadShader(const char* text, GLenum type)
	{
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
				Util::DebugPrintF("ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex");
				glGetShaderInfoLog(shader, 8192, &log_length, info_log);
				Util::DebugPrintF("ERROR: \n%s\n\n", info_log);
				glDeleteShader(shader);
				shader = 0;
			}
		}

		return shader;
	}

	inline std::string LoadShaderFromFile(const char* filename)
	{
		std::ifstream ifile(filename);
		std::string outstr;
		getline(ifile, outstr, '\0');

		return outstr;
	}

	inline GLuint LoadShaders(ShaderInfo* shaders)
	{
		if (shaders == nullptr)
		{
			return 0;
		}

		GLuint program = glCreateProgram();

		ShaderInfo* entry = shaders;
		while (entry->type != GL_NONE) {
			GLuint shader = glCreateShader(entry->type);

			entry->shader = shader;

			std::string src = LoadShaderFromFile(entry->filename);

			if (src.length() == 0) {

				for (entry = shaders; entry->type != GL_NONE; ++entry) {
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
			if (!compiled) {
#ifdef _DEBUG
				GLsizei len;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

				GLchar* log = new GLchar[len + 1];
				glGetShaderInfoLog(shader, len, &len, log);
				DebugPrintF("Shader compilation failed: %s\n", log);
				delete[] log;
#endif /* DEBUG */

				return 0;
			}

			glAttachShader(program, shader);

			++entry;
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
#ifdef _DEBUG
			GLsizei len;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, &len, log);
			DebugPrintF("Shader linking failed: %s\n", log);
			delete[] log;
#endif /* DEBUG */

			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		return program;
	}
}

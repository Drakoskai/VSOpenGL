#pragma once

#include "glad.h"

struct ShaderInfo
{
	GLenum type;
	const char* filename;
	GLuint shader;
};

namespace Util
{
	GLuint LoadShader(const char* text, GLenum type);

	std::string LoadShaderFromFile(const char* filename);

	GLuint LoadShaders(ShaderInfo* shaders);
}

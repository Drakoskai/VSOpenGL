#pragma once

#include "glad.h"
#include <vector>

namespace OpenGL
{
	struct ShaderInfo
	{
		GLenum type;
		const char* filename;
		GLuint shader;
	};
	
	class Shader
	{
	public:
		Shader(std::vector<ShaderInfo> shaders);
		~Shader();
		void Set() const;
		static void Unset();
		static GLuint LoadShader(const char* text, GLenum type);
		std::string LoadShaderFromFile(const char* filename) const;
		GLuint LoadShaders(ShaderInfo* shaders) const;

		GLuint m_shaderProg;
		GLint m_uniformMVP;
		GLint m_uniformModelView;
		uint32_t m_numShaders;

		std::vector<ShaderInfo> m_shaderInfo;
	};
}

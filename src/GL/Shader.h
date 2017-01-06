#pragma once

#include "glad.h"
#include <vector>
#include "../Math3d/Vector.h"
#include "../Math3d/Matrix.h"

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
		void SetFloat(const char *name, float value, bool useShader = false) const;
		void SetInteger(const char *name, uint32_t value, bool useShader = false) const;
		void SetVector2f(const char *name, float x, float y, bool useShader = false) const;
		void SetVector2f(const char *name, const Math3d::Vector2f &value, bool useShader = false) const;
		void SetVector3f(const char *name, float x, float y, float z, bool useShader = false) const;
		void SetVector3f(const char *name, const Math3d::Vector3f &value, bool useShader = false) const;
		void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false) const;
		void SetVector4f(const char *name, const Math3d::Vector4f &value, bool useShader = false) const;
		void SetMatrix4(const char *name, const Math3d::Matrix &matrix, bool useShader = false) const;
		static uint32_t LoadShader(const char* text, GLenum type);
		std::string LoadShaderFromFile(const char* filename) const;
		uint32_t LoadShaders(ShaderInfo* shaders) const;

	private:
		uint32_t m_shaderProg;
		std::vector<ShaderInfo> m_shaderInfo;
		uint32_t m_numShaders;
	};
}

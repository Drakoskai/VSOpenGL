#pragma once

#include "../GL/glad.h"
#include "../Model/Vertex.h"
#include <cstdint>
#include <vector>

namespace OpenGL
{
	class VertexBufferObject
	{
		struct VBOInfo
		{
			uint32_t size;
			uint32_t numAttribs;
			uint32_t numVertices;
			uint32_t numIndices;
			uint32_t stride;
		};

		struct AttribInfo
		{
			GLint size;
			GLenum type;
			GLboolean normalized;
			size_t offset;
		};

	public:
		VertexBufferObject();
		~VertexBufferObject();
		void Load(const char* filename);
		void SetAttributes(AttribInfo* m_attributes);
		void Create(std::vector<Model::Vertex> vertices, std::vector<uint32_t> indices);
		void Render() const;

	private:
		void GatherInfo(const std::vector<Model::Vertex>& verts, const std::vector<GLuint>& indices);
		void CreateAttribute(GLuint const index, const GLvoid* pointer) const;

		GLuint m_vao;
		GLuint m_attributeBuffer;
		GLuint m_indexBuffer;
		GLenum m_mode;
		VBOInfo m_info;

		AttribInfo* m_attributes;
	};
}

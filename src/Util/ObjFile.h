#pragma once

#include <vector>
#include "../Math3d/Vector.h"
#include "../Model/Vertex.h"

namespace Util
{
	class ObjFile
	{

	public:
		ObjFile(std::string filename);
		~ObjFile();

		bool Exists();
		void GetVertices(std::vector<Model::Vertex>& vertices, std::vector<GLuint>& indices);
		std::string ToString();

	private:
		void LoadData();

		bool m_exists;
		bool m_isLoaded;

		std::string m_filename;
		std::vector<Math3d::Vector3f> m_positions;
		std::vector<Math3d::Vector3f> m_normals;
		std::vector<Math3d::Vector2f> m_uvs;
		std::vector<GLuint> m_vertIndices;
		std::vector<GLuint> m_normalIndices;
		std::vector<GLuint> m_uvIndices;
	};
}
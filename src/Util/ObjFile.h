#pragma once

#include <vector>
#include "../Math3d/Vector.h"
#include "../Model/Vertex.h"

namespace Util
{
	struct MeshVert
	{
		uint16_t posIdx;
		uint16_t normIdx;
		uint16_t uvIdx;
		bool hasUv;
		bool hasPos;
		bool hasNorm;
	};

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

		static void ConsumeToEOL(std::fstream& stream);

		std::string m_filename;
		std::vector<Math3d::Vector3f> m_positions;
		std::vector<Math3d::Vector3f> m_normals;
		std::vector<Math3d::Vector2f> m_uvs;
		std::vector<MeshVert> m_faceIndices;
		std::vector<GLuint> m_vertIndices;
		std::vector<GLuint> m_normalIndices;
		std::vector<GLuint> m_uvIndices;
	};
}
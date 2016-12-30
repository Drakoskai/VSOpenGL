#include "../pch.h"
#include "ObjFile.h"
#include "Util.h"

namespace Util{

	using namespace std;

	ObjFile::ObjFile(std::string filename)
		: m_exists(false), m_isLoaded(false), m_filename(filename) { }

	ObjFile::~ObjFile() { }

	bool ObjFile::Exists()
	{
		fstream fileStream;
		if (!fileStream.is_open())
		{
			fileStream.open(m_filename);
			m_exists = !fileStream.fail();
		}
		fileStream.close();

		return m_exists;
	}

	void ObjFile::GetVertices(vector<Model::Vertex>& vertices, vector<GLuint>& indices)
	{
		using namespace Math3d;
		using namespace Model;
		if (!m_isLoaded)
		{
			LoadData();
		}

		size_t numVertices = m_faceIndices.size();

		for (uint32_t i = 0; i < numVertices; i++){
			MeshVert face = m_faceIndices[i];
			Vertex v;
			if (face.hasPos)
			{
				uint16_t posidx = face.posIdx;
				v.position = m_positions[posidx - 1];
			}
			if (face.hasNorm)
			{
				uint16_t normidx = m_faceIndices[i].normIdx;
				v.normal = m_normals[normidx - 1];
			}
			if (face.hasUv)
			{
				uint16_t uvidx = m_faceIndices[i].hasUv;
			}

			vertices.push_back(v);

			indices.push_back(static_cast<GLuint>(vertices.size()) - 1);
		}
	}

	void ObjFile::LoadData()
	{
		using namespace Math3d;
		if (!Exists())
		{
			return;
		}
		fstream fileStream;
		fileStream.open(m_filename);

		uint16_t format = 0;
		char input;
		string material;
		string name;
		fileStream.get(input);
		uint32_t sides = 0;
		while (!fileStream.eof())
		{
			switch (input)
			{
			case '#':
			{
				ConsumeToEOL(fileStream);
			}
			break;
			case 'u':
			{
				while (input != ' ')
				{
					fileStream.get(input);
				}
				fileStream >> material;
				//DebugPrintF("Material: %s\n", material.c_str());
			}
			break;
			case 'o':
			{
				fileStream >> name;
				//DebugPrintF("name: %s\n", name.c_str());
			}
			break;

			case 'v':
			{
				fileStream.get(input);
				if (input == ' ')
				{
					Vector3f vert;
					fileStream >> vert;
					m_positions.push_back(vert);
				}
				else if (input == 't')
				{
					Vector2f tex;
					fileStream >> tex;
					m_uvs.push_back(tex);
				}
				else if (input == 'n')
				{
					Vector3f norm;
					fileStream >> norm;
					m_normals.push_back(norm);
				}
				ConsumeToEOL(fileStream);
			}
			break;
			case 's':
			{
				sides++;
			}
			break;
			case 'f':
			{
				if (format == 0)
				{
					//formats
					// 1  #
					// 2  #/#
					// 3  #/#/#
					// 4  #//#
					if (m_positions.size() > 0 && m_uvs.size() == 0 && m_normals.size() == 0)
					{
						format = 1;
					}
					else if (m_positions.size() > 0 && m_uvs.size() > 0 && m_normals.size() == 0)
					{
						format = 2;
					}
					else if (m_positions.size() > 0 && m_uvs.size() > 0 && m_normals.size() > 0)
					{
						format = 3;
					}
					else if (m_positions.size() > 0 && m_uvs.size() == 0 && m_normals.size() > 0)
					{
						format = 4;
					}
				}
				char garbage;
				uint16_t vertidx1;
				uint16_t vertidx2;
				uint16_t vertidx3;
				uint16_t uvidx1;
				uint16_t uvidx2;
				uint16_t uvidx3;
				uint16_t normalidx1;
				uint16_t normalidx2;
				uint16_t normalidx3;
				switch (format)
				{
				case 1:
				{
					// 1 #
					fileStream >> vertidx1 >> vertidx2 >> vertidx3;

					MeshVert vert1;
					vert1.posIdx = vertidx1;
					vert1.hasPos = true;
					vert1.hasNorm = false;
					vert1.hasUv = false;

					m_faceIndices.push_back(vert1);

					MeshVert vert2;
					vert2.posIdx = vertidx2;
					vert2.hasPos = true;
					vert2.hasNorm = false;
					vert2.hasUv = false;
					m_faceIndices.push_back(vert2);

					MeshVert vert3;
					vert3.hasPos = true;
					vert3.hasNorm = false;
					vert3.posIdx = vertidx3;
					vert3.hasUv = false;

					m_faceIndices.push_back(vert3);
				}
				break;
				case 2:
				{
					// 2  #/#
					fileStream >> vertidx1 >> garbage >> uvidx1
						>> vertidx2 >> garbage >> uvidx2
						>> vertidx3 >> garbage >> uvidx3;

					MeshVert vert1;
					vert1.posIdx = vertidx1;
					vert1.uvIdx = uvidx1;
					vert1.hasPos = true;
					vert1.hasNorm = false;
					vert1.hasUv = true;

					m_faceIndices.push_back(vert1);

					MeshVert vert2;
					vert2.posIdx = vertidx2;
					vert2.uvIdx = uvidx3;
					vert2.hasPos = true;
					vert2.hasNorm = false;
					vert2.hasUv = true;
					m_faceIndices.push_back(vert2);

					MeshVert vert3;
					vert3.hasPos = true;
					vert3.hasNorm = false;
					vert3.posIdx = vertidx3;
					vert3.uvIdx = uvidx3;
					vert3.hasUv = true;

					m_faceIndices.push_back(vert3);
				}
				break;
				case 3:
				{
					// 3  #/#/#
					fileStream >> vertidx1 >> garbage >> uvidx1 >> garbage >> normalidx1
						>> vertidx2 >> garbage >> uvidx2 >> garbage >> normalidx2
						>> vertidx3 >> garbage >> uvidx3 >> garbage >> normalidx3;

					MeshVert vert1;
					vert1.posIdx = vertidx1;
					vert1.normIdx = normalidx1;
					vert1.uvIdx = uvidx1;
					vert1.hasPos = true;
					vert1.hasNorm = true;
					vert1.hasUv = true;

					m_faceIndices.push_back(vert1);

					MeshVert vert2;
					vert2.posIdx = vertidx2;
					vert2.normIdx = normalidx2;
					vert2.uvIdx = uvidx3;
					vert2.hasPos = true;
					vert2.hasNorm = true;
					vert2.hasUv = true;
					m_faceIndices.push_back(vert2);

					MeshVert vert3;
					vert3.hasPos = true;
					vert3.hasNorm = true;
					vert3.posIdx = vertidx3;
					vert3.normIdx = normalidx3;
					vert3.uvIdx = uvidx3;
					vert3.hasUv = true;

					m_faceIndices.push_back(vert3);
				}
				break;
				case 4:
				{
					// 3  #/#/#
					fileStream >> vertidx1 >> garbage >> garbage >> normalidx1
						>> vertidx2 >> garbage >> garbage >> normalidx2
						>> vertidx3 >> garbage >> garbage >> normalidx3;

					MeshVert vert1;
					vert1.posIdx = vertidx1;
					vert1.normIdx = normalidx1;
					vert1.hasPos = true;
					vert1.hasNorm = true;
					m_faceIndices.push_back(vert1);

					MeshVert vert2;
					vert2.posIdx = vertidx2;
					vert2.normIdx = normalidx2;
					vert2.hasPos = true;
					vert2.hasNorm = true;
					m_faceIndices.push_back(vert2);

					MeshVert vert3;
					vert3.hasPos = true;
					vert3.hasNorm = true;
					vert3.posIdx = vertidx3;
					vert3.normIdx = normalidx3;
					m_faceIndices.push_back(vert3);
				}
				break;

				default:
					break;
				}
				ConsumeToEOL(fileStream);
			}
			default:
				break;
			}
			fileStream.get(input);
		}
		fileStream.close();
		m_isLoaded = true;
	}

	void ObjFile::ConsumeToEOL(fstream& stream)
	{
		char input;
		input = stream.peek();
		while (input != '\n')
		{
			stream.get(input);
		}
	}

	string ObjFile::ToString()
	{
		if (!m_isLoaded)
		{
			LoadData();
		}

		stringstream ss;
		ss << m_filename
			<< ':'
			<< '{' << endl;
		ss << '\t';
		ss << "vertices:[" << endl;
		unsigned int count = 0;

		for (Math3d::Vector3f vert : m_positions)
		{
			ss << '\t';
			ss << '\t';
			ss << '{' << "x:" << vert.x << ','
				<< "y:" << vert.y << ','
				<< "z:" << vert.z << "}";
			count++;
			if (count < m_positions.size())
			{
				ss << ',';
			}
			ss << endl;
		}
		ss << '\t';
		ss << '\t';
		ss << "]," << endl;

		ss << '\t';
		ss << "normals:[" << endl;

		count = 0;
		for (Math3d::Vector3f norm : m_normals)
		{
			ss << '\t';
			ss << '\t';
			ss << '{' << "x:" << norm.x << ','
				<< "y:" << norm.y << ','
				<< "z:" << norm.z << "}";
			count++;
			if (count < m_normals.size())
			{
				ss << ',';
			}
			ss << endl;
		}

		ss << '\t';
		ss << '\t';
		ss << "]," << endl;

		ss << '\t';
		ss << "uvs:[" << endl;

		count = 0;
		for (Math3d::Vector2f tex : m_uvs)
		{
			ss << '\t';
			ss << '\t';
			ss << '{' << "x:" << tex.x << ','
				<< "y:" << tex.y << '}';
			count++;
			if (count < m_uvs.size())
			{
				ss << ',';
			}
			ss << endl;
		}
		ss << '\t';
		ss << '\t';
		ss << ']' << endl;



		ss << '\t';
		ss << "VertexIndices:[" << endl;

		count = 0;
		size_t indicesSize = m_vertIndices.size();
		for (int i = 0; i < indicesSize; i++)
		{
			ss << '\t';
			ss << '\t';
			ss << '{' << "vi:" << m_vertIndices[i] << ','
				<< "ti:" << m_uvIndices[i] << ','
				<< "ni:" << m_normalIndices[i] << "}";
			count++;
			if (count < indicesSize)
			{
				ss << ',';
			}
			ss << endl;
		}

		ss << '\t';
		ss << '\t';
		ss << "]," << endl;
		ss << '\t';
		ss << '}' << endl;

		return ss.str();
	}
}

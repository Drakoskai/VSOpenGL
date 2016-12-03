#include "ObjFile.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Util.h"
#include "Vector.h"
#include <regex>
#include "Vertex.h"

using namespace std;

ObjFile::ObjFile(string filename)
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

void ObjFile::GetMeshData(vector<Vector3f>& positions, vector<Vector2f>& uvs, vector<Vector3f>& normals, vector<GLuint>& indices)
{
	if (!m_isLoaded)
	{
		LoadData();
	}

	for (unsigned int i = 0; i < m_vertIndices.size(); i++){
		unsigned int vertexIndex = m_vertIndices[i];
		
		unsigned int normalIndex = m_normalIndices[i];

		Vector3f pos = m_verts[vertexIndex - 1];
		if (m_uvs.size() > 0)
		{
			unsigned int uvIndex = m_uvIndices[i];
			Vector2f uv = m_uvs[uvIndex - 1];
			uvs.push_back(uv);
		}
		
		Vector3f normal = m_normals[normalIndex - 1];

		positions.push_back(pos);
		
		normals.push_back(normal);
		indices.push_back(static_cast<GLuint>(positions.size()) - 1);
	}
}

void ObjFile::GetMeshData(vector<Vertex>& vertices, vector<GLuint>& indices)
{
	if (!m_isLoaded)
	{
		LoadData();
	}

	for (unsigned int i = 0; i < m_vertIndices.size(); i++){
		unsigned int vertexIndex = m_vertIndices[i];
		Vertex v;
		v.position = m_verts[vertexIndex - 1];
		v.normal = m_normals[vertexIndex - 1];

		vertices.push_back(v);

		indices.push_back(static_cast<GLuint>(vertices.size()) - 1);
	}
}

void ObjFile::LoadData()
{
	if (!Exists())
	{
		return;
	}
	fstream fileStream;
	fileStream.open(m_filename);

	char input;
	fileStream.get(input);
	while (!fileStream.eof())
	{
		if (input == 'v')
		{
			fileStream.get(input);
			if (input == ' ')
			{
				float x;
				float y;
				float z;
				fileStream >> x;
				fileStream >> y;
				fileStream >> z;

				Vector3f vert = Vector3f(x, y, z);
				m_verts.push_back(vert);
			}
			else if (input == 't')
			{
				float x;
				float y;
				fileStream >> x;
				fileStream >> y;

				Vector2f tex = Vector2f(x, y);
				m_uvs.push_back(tex);
			}
			else if (input == 'n')
			{
				float x;
				float y;
				float z;
				fileStream >> x;
				fileStream >> y;
				fileStream >> z;

				Vector3f norm = Vector3f(x, y, z);
				m_normals.push_back(norm);
			}
		}
		else if (input == 'f')
		{
			fileStream.get(input);
			if (input == ' ')
			{
				char garbage;
				GLuint vertidx1;
				GLuint vertidx2;
				GLuint vertidx3;
				GLuint uvidx1;
				GLuint uvidx2;
				GLuint uvidx3;
				GLuint normalidx1;
				GLuint normalidx2;
				GLuint normalidx3;
				if (m_uvs.size() == 0)
				{
					fileStream >> vertidx1 >> garbage >> garbage >> normalidx1
						>> vertidx2 >> garbage >> garbage >> normalidx2
						>> vertidx3 >> garbage >> garbage >> normalidx3;

					m_vertIndices.push_back(vertidx1);
					m_vertIndices.push_back(vertidx2);
					m_vertIndices.push_back(vertidx3);

		  		    m_normalIndices.push_back(normalidx1);
					m_normalIndices.push_back(normalidx2);
					m_normalIndices.push_back(normalidx3);
				}
				else
				{

					fileStream >> vertidx1 >> garbage >> uvidx1 >> garbage >> normalidx1
						>> vertidx2 >> garbage >> uvidx2 >> garbage >> normalidx2
						>> vertidx3 >> garbage >> uvidx3 >> garbage >> normalidx3;

					m_vertIndices.push_back(vertidx1);
					m_vertIndices.push_back(vertidx2);
					m_vertIndices.push_back(vertidx3);

					m_uvIndices.push_back(uvidx1);
					m_uvIndices.push_back(uvidx2);
					m_uvIndices.push_back(uvidx3);

					m_normalIndices.push_back(normalidx1);
					m_normalIndices.push_back(normalidx2);
					m_normalIndices.push_back(normalidx3);
				}
			}
		}

		while (input != '\n')
		{
			fileStream.get(input);
		}
		fileStream.get(input);
	}

	fileStream.close();
	m_isLoaded = true;
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

	for (Vector3f vert : m_verts)
	{
		ss << '\t';
		ss << '\t';
		ss << '{' << "x:" << vert.x << ','
			<< "y:" << vert.y << ','
			<< "z:" << vert.z << "}";
		count++;
		if (count < m_verts.size())
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
	for (Vector3f norm : m_normals)
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
	for (Vector2f tex : m_uvs)
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

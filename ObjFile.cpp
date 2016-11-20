#include "ObjFile.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Util.h"
#include "Vector.h"

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

void ObjFile::GetVertices(std::vector<Vector3f>& vertices)
{
	if (!m_isLoaded)
	{
		LoadData();
	}

	vertices = m_verts;
}

void ObjFile::GetNormals(std::vector<Vector3f>& normals)
{
	if (!m_isLoaded)
	{
		LoadData();
	}

	normals = m_normals;
}

void ObjFile::GetUVs(std::vector<Vector2f>& uvs)
{
	if (!m_isLoaded)
	{
		LoadData();
	}

	uvs = m_uvs;
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
	int count = 0;

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
	ss << '}' << endl;

	return ss.str();
}

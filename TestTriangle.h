#pragma once

class TestTriangle
{
private:
	struct VertexType
	{
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;
	};

public:
	TestTriangle();
	~TestTriangle();

	void Init();
	void Draw() const;
	void Release() const;
private:
	int m_vertexCount;
	int m_indexCount;
	unsigned int m_vertexArrayId;
	unsigned int m_vertexBufferId;
	unsigned int m_indexBufferId;
	unsigned int m_shaderProgram;
};
#include "Model.h"


Model::Model(float** vertices, int numVerts, GLint*** elements, int numElements, int numPerFace)
	: m_vao(0), m_shaderProg(0), m_vPosition(0), m_PersLoc(0), m_modelViewLoc(0), m_buffers(nullptr),
	m_numVerts(numVerts), m_numElements(numElements), m_numPerFace(numPerFace), m_UniInnerLoc(0),
	m_UniOuterLoc(0), m_vertices(nullptr), m_elements(nullptr)
{
	m_vertices = new float*[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		m_vertices[i] = new float[3];
		for (int j = 0; j < 3; j++)
		{
			m_vertices[i][j] = vertices[i][j];
		}
	}

	m_elements = new GLint**[numElements];
	for (int i = 0; i < numElements; i++)
	{
		GLint ** temp = new GLint*[4];
		for (int j = 0; j < numElements; j++)
		{
			temp[j] = new GLint[4];
			for (int k = 0; k < 4; k++)
			{
				temp[j][k] = elements[i][j][k];
			}
		}
		m_elements[i] = temp;
	}
}

Model::~Model()
{
	Release();
	
}

void Model::Init(DrawContext& dc)
{
	m_buffers = new GLuint[NumVertexBuffers];

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(NumVertexBuffers, m_buffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[ElementBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_elements), m_elements, GL_STATIC_DRAW);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "teapot.vert" },
		{ GL_TESS_CONTROL_SHADER, "teapot.cont" },
		{ GL_TESS_EVALUATION_SHADER, "teapot.eval" },
		{ GL_FRAGMENT_SHADER, "teapot.frag" },
		{ GL_NONE, nullptr }
	};

	m_shaderProg = dc.LoadShader(shaders);
	glUseProgram(m_shaderProg);

	m_vPosition = glGetAttribLocation(m_shaderProg, "vPosition");
	glEnableVertexAttribArray(m_vPosition);
	glVertexAttribPointer(m_vPosition, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));

	m_PersLoc = glGetUniformLocation(m_shaderProg, "P");
	m_modelViewLoc = glGetUniformLocation(m_shaderProg, "MV");

	m_UniInnerLoc = glGetUniformLocation(m_shaderProg, "Inner");
	m_UniOuterLoc = glGetUniformLocation(m_shaderProg, "Outer");

	glUniform1f(m_UniInnerLoc, m_tessInner);
	glUniform1f(m_UniOuterLoc, m_tessOuter);

	m_transform = Transform();
	m_transform.Translate(Vector3f(-0.2625f, -1.575f, -1.0f));
	m_transform.Translate(Vector3f(0.0f, 0.0f, -7.5f));

	glUniformMatrix4fv(m_modelViewLoc, 1, GL_TRUE, m_transform.GetModelView());

	glPatchParameteri(GL_PATCH_VERTICES, m_numPerFace);

	/*for (int i = 0; i < m_numVerts; i++)
	{
		delete[] m_vertices[i];
	}

	delete[] m_vertices;

	for (int i = 0; i < m_numElements; i++)
	{
		GLint** temp = m_elements[i];
		for (int j = 0; j < 4; j++)
		{
			GLint* temptemp = temp[j];
			delete[] temptemp;
		}
		delete[] temp;
	}

	delete[] m_elements;*/
}

Transform Model::GetTransform() const { return m_transform; }

void Model::Update(const Matrix& proj)
{
	m_transform.Update();
	glUniformMatrix4fv(m_modelViewLoc, 1, GL_TRUE, m_transform.GetModelView());
	glUniformMatrix4fv(m_PersLoc, 1, GL_TRUE, proj);
}

void Model::Draw() const
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_PATCHES, m_numPerFace, GL_UNSIGNED_INT, static_cast<void*>(nullptr));
}

void Model::Release() const
{
	glDeleteBuffers(NumVertexBuffers, m_buffers);
	if (m_buffers)
	{
		delete[] m_buffers;
	}
}

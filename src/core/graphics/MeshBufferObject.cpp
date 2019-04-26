#include "MeshBufferObject.h"

MeshBufferObject::MeshBufferObject()
{
	m_iNumberOfIndices = 0;
}

MeshBufferObject::~MeshBufferObject()
{
	glDeleteVertexArrays(1, &m_Mesh);

	glDeleteBuffers(1, &m_Vertices);
	glDeleteBuffers(1, &m_Indices);
	glDeleteBuffers(1, &m_Normals);
	glDeleteBuffers(1, &m_TexCoords);
	glDeleteBuffers(1, &m_Tangents);
	glDeleteBuffers(1, &m_MiscValues);
	glDeleteBuffers(1, &m_MiscValues2);
}

void MeshBufferObject::bindVertices(const std::vector<ci::vec3>& vertices)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(ci::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindVertices(const float* vertices, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void MeshBufferObject::bindIndices(const std::vector<unsigned int>& indices)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Indices);
	glBufferData(GL_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);
	m_iNumberOfIndices = indices.size();

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindIndices(const int* indices, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Indices);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(int), indices, GL_STATIC_DRAW);
	m_iNumberOfIndices = size;

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void MeshBufferObject::bindNormals(const std::vector<ci::vec3>& normals)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(ci::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindNormals(const float* normals, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void MeshBufferObject::bindTexCoords(const std::vector<ci::vec2>& texCoords)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoords);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size()*sizeof(ci::vec2), &texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindTexCoords(const float* texCoords, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_TexCoords);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindTangents(const std::vector<ci::vec3>& tangents)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Tangents);
	glBufferData(GL_ARRAY_BUFFER, tangents.size()*sizeof(ci::vec3), &tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindTangents(const float* tangents, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_Tangents);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), tangents, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindMiscValues(const std::vector<float>& values)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_MiscValues);
	glBufferData(GL_ARRAY_BUFFER, values.size()*sizeof(float), &values[0], GL_STATIC_DRAW);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(4);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindMiscValues(const float* values, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_MiscValues);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), values, GL_STATIC_DRAW);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(4);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindMiscValues2(const std::vector<float>& values)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_MiscValues2);
	glBufferData(GL_ARRAY_BUFFER, values.size()*sizeof(float), &values[0], GL_STATIC_DRAW);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(5);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::bindMiscValues2(const float* values, const int size)
{
	glBindVertexArray(m_Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_MiscValues2);
	glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), values, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(5);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshBufferObject::generateBuffers()
{
	glGenVertexArrays(1, &m_Mesh);

	glGenBuffers(1, &m_Vertices);
	glGenBuffers(1, &m_Indices);
	glGenBuffers(1, &m_Normals);
	glGenBuffers(1, &m_TexCoords);
	glGenBuffers(1, &m_Tangents);
	glGenBuffers(1, &m_MiscValues);
	glGenBuffers(1, &m_MiscValues2);
}

void MeshBufferObject::bindVertexArray()
{
	glBindVertexArray(m_Mesh);
}

void MeshBufferObject::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indices);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_iNumberOfIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
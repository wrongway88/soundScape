#ifndef MESH_BUFFER_OBJECT_H
#define MESH_BUFFER_OBJECT_H

#include "cinder\gl\gl.h"

class MeshBufferObject
{
public:
	MeshBufferObject();
	~MeshBufferObject();

	void bindVertices(const std::vector<ci::Vec3f>& vertices);
	void bindVertices(const float* vertices, const int size);

	void bindIndices(const std::vector<unsigned int>& indices);
	void bindIndices(const int* indices, const int size);

	void bindNormals(const std::vector<ci::Vec3f>& normals);
	void bindNormals(const float* normals, const int size);

	void bindTexCoords(const std::vector<ci::Vec2f>& texCoords);
	void bindTexCoords(const float* texCoords, const int size);

	void bindTangents(const std::vector<ci::Vec3f>& tangents);
	void bindTangents(const float* tangents, const int size);

	void bindMiscValues(const std::vector<float>& values);
	void bindMiscValues(const float* values, const int size);

	void bindMiscValues2(const std::vector<float>& values);
	void bindMiscValues2(const float* values, const int size);

	void generateBuffers();

	void bindVertexArray();

	void draw();

private:
	GLuint m_Mesh;

	GLuint m_Vertices; //location 0
	GLuint m_Indices; //no attribute pointer for indices
	GLuint m_Normals; //location 1
	GLuint m_TexCoords; //location 2
	GLuint m_Tangents; //location 4 (just kidding, it's 3)
	GLuint m_MiscValues; // location 4 for misc values
	GLuint m_MiscValues2;

	unsigned int m_iNumberOfIndices;
};

#endif
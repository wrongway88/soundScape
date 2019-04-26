#ifndef SHADER_H
#define SHADER_H

#include "cinder\gl\gl.h"
#include "cinder\Vector.h"
#include "cinder\Matrix44.h"

class Shader
{
public:
	Shader();
	~Shader();

	void load(const std::string& vertexPath, const std::string& fragmentPath);
	void load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath);

	void bind();
	void unbind();

	void setUniform(const std::string& name, int value);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, const ci::vec3& value);
	void setUniform(const std::string& name, const ci::vec4& value);
	void setUniform(const std::string& name, const ci::mat3& value, bool transpose);
	void setUniform(const std::string& name, const ci::mat4& value, bool transpose);

	void bindAttribute(const GLuint index, const std::string& name);
	void bindFragDataLocation(const GLuint index, const std::string& name);

	void linkShaders();

private:
	GLuint createShader(const std::string& path, const GLenum& type);
	void createProgram();

	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_GeometryShader;

	GLuint m_GlslProgram;
};

#endif
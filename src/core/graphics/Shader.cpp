#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
	glDeleteProgram(m_GlslProgram);

	glDeleteShader(m_VertexShader);
	glDeleteShader(m_GeometryShader);
	glDeleteShader(m_FragmentShader);
}

void Shader::load(const std::string& vertexPath, const std::string& fragmentPath)
{
	m_VertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
	m_FragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);

	createProgram();
}

void Shader::load(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath)
{
	m_VertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
	m_GeometryShader = createShader(geometryPath, GL_GEOMETRY_SHADER_ARB);
	m_FragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);
	
	createProgram();
}

void Shader::bind()
{
	glUseProgram(m_GlslProgram);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setUniform(const std::string& name, int value)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniform1i(location, value);
}

void Shader::setUniform(const std::string& name, float value)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, const ci::Vec3f& value)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const ci::Vec4f& value)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, const ci::Matrix33f& value, bool transpose)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniformMatrix3fv(location, 1, transpose, &value[0]);
}

void Shader::setUniform(const std::string& name, const ci::Matrix44f& value, bool transpose)
{
	GLuint location = glGetUniformLocation( m_GlslProgram, name.c_str() );
	glUniformMatrix4fv(location, 1, transpose, &value[0]);
}

void Shader::bindAttribute(const GLuint index, const std::string& name)
{
	glBindAttribLocation(m_GlslProgram, index, name.c_str());
}

void Shader::bindFragDataLocation(const GLuint index, const std::string& name)
{
	glBindFragDataLocation(m_GlslProgram, index, name.c_str());
}

void Shader::linkShaders()
{
	glLinkProgram(m_GlslProgram);
}

GLuint Shader::createShader(const std::string& path, const GLenum& type)
{
	try
	{	
		std::string source;
		std::string line;
		std::ifstream file(path.c_str());

		GLuint shader = glCreateShader(type);

		if (!file.is_open())
		{
			throw 0;
		}
		while (!file.eof()) 
		{
			getline(file, line);
			source.append(line);
			source.append("\n");
		}
		file.close();

		const char* s = source.c_str();
		glShaderSource(shader, 1, &s, 0);
		glCompileShader(shader);

		GLint sz = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &sz);
		if (sz > 0)
		{
			char* buffer = new char[sz];
			memset(buffer, 0, sz);

			glGetShaderInfoLog(shader, sz, NULL, buffer);
			std::cout << "shader log: " << buffer << std::endl;

			delete[] buffer;
		}

		return shader;
	}
	catch (...)
	{
		std::cout << "error: shader could not be compiled" << std::endl;
		return 0;
	}
}

void Shader::createProgram()
{
	m_GlslProgram = glCreateProgram();

	glAttachShader(m_GlslProgram, m_VertexShader);
	if(m_GeometryShader) glAttachShader(m_GlslProgram, m_GeometryShader);
	glAttachShader(m_GlslProgram, m_FragmentShader);
}


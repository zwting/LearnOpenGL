#include "Shader.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragPath)
{
	assert(vertexPath && fragPath);

	try
	{
		std::fstream vertexStream(vertexPath, std::ios_base::in);
		std::fstream fragStream(fragPath, std::ios_base::in);
		std::stringstream vertexBuffer;
		std::stringstream fragBuffer;

		vertexBuffer << vertexStream.rdbuf();
		_vertexSrc = vertexBuffer.str();
		vertexStream.close();

		fragBuffer << fragStream.rdbuf();
		_fragSrc = fragBuffer.str();
		fragStream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error: shader file not successfuly read" << std::endl;
	}

	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexCSrc = _vertexSrc.c_str();
	if (!Compile(_vertexID, vertexCSrc))
		return;

	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSrc = _fragSrc.c_str();
	if (!Compile(_fragmentID, fragmentSrc))
		return;

	_program = glCreateProgram();

	glAttachShader(_program, _vertexID);
	glAttachShader(_program, _fragmentID);
	glLinkProgram(_program);

	int success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(_logBuffer, 0, sizeof(_logBuffer));
		glGetProgramInfoLog(_program, sizeof(_logBuffer) / sizeof(char), nullptr, _logBuffer);
		std::cout << "Error: Shader program linking failed:\n" << _logBuffer << std::endl;
		return;
	}

	glDeleteShader(_vertexID);
	glDeleteShader(_fragmentID);
}

void Shader::SetVec4(const char* variable, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
	const GLint location = glGetUniformLocation(this->_program, variable);
	glUniform4f(location, x, y, z, w);
}

void Shader::SetVec3(const char* variable, const vec3& val) const
{
	const GLint location = glGetUniformLocation(this->_program, variable);
	glUniform3f(location, val.x, val.y, val.z);
}


void Shader::SetFloat(const char* variable, float val) const

{
	const GLint location = glGetUniformLocation(this->_program, variable);
	glUniform1f(location, val);
}

void Shader::SetInt(const char* variable, int val) const
{
	const GLint location = glGetUniformLocation(this->_program, variable);
	glUniform1i(location, val);
}

void Shader::SetMat4vf(const char* variable, const GLfloat* val) const
{
	const GLint location = glGetUniformLocation(this->_program, variable);
	glUniformMatrix4fv(location, 1, GL_FALSE, val);
}

void Shader::Use() const
{
	glUseProgram(_program);
}


bool Shader::Compile(GLuint shaderID, const char* src)
{
	glShaderSource(shaderID, 1, &src, nullptr);

	glCompileShader(shaderID);
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		memset(_logBuffer, 0, sizeof(_logBuffer));
		glGetShaderInfoLog(shaderID, sizeof(_logBuffer) / sizeof(char), nullptr, _logBuffer);
		std::cout << "Error: vertex shader compilation failed:\n" << _logBuffer << std::endl;
		return false;
	}

	return true;
}

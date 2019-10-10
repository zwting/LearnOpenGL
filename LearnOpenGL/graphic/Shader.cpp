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
		mVertexSrc = vertexBuffer.str();
		vertexStream.close();

		fragBuffer << fragStream.rdbuf();
		mFragSrc = fragBuffer.str();
		fragStream.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error: shader file not successfuly read" << std::endl;
	}

	mVertexID = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexCSrc = mVertexSrc.c_str();
	if (!Compile(mVertexID, vertexCSrc))
		return;

	mFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSrc = mFragSrc.c_str();
	if (!Compile(mFragmentID, fragmentSrc))
		return;

	mProgram = glCreateProgram();

	glAttachShader(mProgram, mVertexID);
	glAttachShader(mProgram, mFragmentID);
	glLinkProgram(mProgram);

	int success;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(mLogBuffer, 0, sizeof(mLogBuffer));
		glGetProgramInfoLog(mProgram, sizeof(mLogBuffer) / sizeof(char), nullptr, mLogBuffer);
		std::cout << "Error: Shader program linking failed:\n" << mLogBuffer << std::endl;
		return;
	}

	glDeleteShader(mVertexID);
	glDeleteShader(mFragmentID);
}

void Shader::SetVec4(const char* variable, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform4f(location, x, y, z, w);
}

void Shader::SetVec3(const char* variable, const vec3& val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform3f(location, val.x, val.y, val.z);
}


void Shader::SetFloat(const char* variable, float val) const

{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform1f(location, val);
}

void Shader::SetInt(const char* variable, int val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform1i(location, val);
}

void Shader::SetMat4vf(const char* variable, const GLfloat* val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniformMatrix4fv(location, 1, GL_FALSE, val);
}

void Shader::Use() const
{
	glUseProgram(mProgram);
}


bool Shader::Compile(GLuint shaderID, const char* src)
{
	glShaderSource(shaderID, 1, &src, nullptr);

	glCompileShader(shaderID);
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		memset(mLogBuffer, 0, sizeof(mLogBuffer));
		glGetShaderInfoLog(shaderID, sizeof(mLogBuffer) / sizeof(char), nullptr, mLogBuffer);
		std::cout << "Error: vertex shader compilation failed:\n" << mLogBuffer << std::endl;
		return false;
	}

	return true;
}

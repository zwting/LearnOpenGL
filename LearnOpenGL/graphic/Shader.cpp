#include "Shader.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragPath, const char* geoPath)
{
	assert(vertexPath && fragPath);

	std::fstream vertexStream(vertexPath);
	std::fstream fragStream(fragPath);
	std::stringstream vertexBuffer;
	std::stringstream fragBuffer;

	vertexBuffer << vertexStream.rdbuf();
	_vertexSrc = vertexBuffer.str();
	vertexStream.close();

	fragBuffer << fragStream.rdbuf();
	_fragSrc = fragBuffer.str();
	fragStream.close();

	if (geoPath)
	{
		std::fstream geoStream(geoPath);
		std::stringstream geoBuffer;
		geoBuffer << geoStream.rdbuf();
		_geoSrc = geoBuffer.str();
		geoStream.close();

		_geometryID = glCreateShader(GL_GEOMETRY_SHADER);
	}

	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);


	_program = glCreateProgram();
	const GLchar* vertexCSrc = _vertexSrc.c_str();
	if (!Compile(_vertexID, vertexCSrc))
		return;

	const GLchar* fragmentSrc = _fragSrc.c_str();
	if (!Compile(_fragmentID, fragmentSrc))
		return;

	glAttachShader(_program, _vertexID);
	glAttachShader(_program, _fragmentID);
	glLinkProgram(_program);

	int success;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(_logBuffer, 0, sizeof(_logBuffer));
		glGetProgramInfoLog(_program, sizeof(_logBuffer) / sizeof(char), nullptr, _logBuffer);
		return;
	}

	glDeleteShader(_vertexID);
	glDeleteShader(_fragmentID);
}

void Shader::Use()
{
	glUseProgram(_program);
}

bool Shader::Compile(GLuint shaderID, const char* src)
{
	glShaderSource(_vertexID, 1, &src, nullptr);

	glCompileShader(shaderID);
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		memset(_logBuffer, 0, sizeof(_logBuffer));
		glGetShaderInfoLog(shaderID, sizeof(_logBuffer) / sizeof(char), nullptr, _logBuffer);
		std::cout << "Error: vertex shader compilation failed:\n" << _logBuffer << std::endl;
		return false;
	}

	return true;
}

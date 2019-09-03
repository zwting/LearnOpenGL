#pragma once
#include <string>
#include <glad/glad.h>
#include "Texture.h"

class Shader
{
private:
	std::string _vertexSrc;
	std::string _fragSrc;

	GLuint _vertexID;
	GLuint _fragmentID;
	GLuint _program;

public:
	GLuint program() const
	{
		return _program;
	}

private:
	char _logBuffer[256];

private:
	bool Compile(GLuint shaderID, const char* src);
public:
	Shader(const char* vertexPath, const char* fragPath);

	void Use() const;

	void SetVec4(const char* variable, float x, float y, float z, float w = 1.0f) const;
	void SetFloat(const char* variable, float val) const;
	void SetInt(const char* variable, int val) const;
	void SetMat4vf(const char* variable, const GLfloat* val)const;
};

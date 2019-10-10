#pragma once
#include <string>
#include <glad/glad.h>
#include "../commons/MathType.h"

class Shader
{
private:
	std::string mVertexSrc;
	std::string mFragSrc;

	GLuint mVertexID;
	GLuint mFragmentID;
	GLuint mProgram;

public:
	GLuint GetProgram() const
	{
		return mProgram;
	}

private:
	char mLogBuffer[256];

private:
	bool Compile(GLuint shaderID, const char* src);
public:
	Shader(const char* vertexPath, const char* fragPath);

	void Use() const;

	void SetVec4(const char* variable, float x, float y, float z, float w = 1.0f) const;
	void SetVec3(const char* variable,const vec3& val)const;
	void SetFloat(const char* variable, float val) const;
	void SetInt(const char* variable, int val) const;
	void SetMat4vf(const char* variable, const GLfloat* val)const;
};

#pragma once
#include <string>
#include <glad/glad.h>

class Shader
{
private:
	std::string _vertexSrc;
	std::string _fragSrc;
	std::string _geoSrc;

	GLuint _vertexID;
	GLuint _fragmentID;
	GLuint _geometryID;
	GLuint _program;

	char _logBuffer[256];

private:
	bool Compile(GLuint shaderID, const char* src);
public:
	Shader(const char* vertexPath, const char* fragPath, const char* geoPath = nullptr);
	void Use();

};

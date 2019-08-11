#pragma once
#include <glad/glad.h>

class Texture
{
public:
	GLint width() const
	{
		return _width;
	}

	GLint height() const
	{
		return _height;
	}

	unsigned char* data() const
	{
		return _data;
	}

	GLint channels() const
	{
		return _channels;
	}

	GLuint id() const
	{
		return _id;
	}

private:
	GLint _width;
	GLint _height;
	unsigned char* _data;
	GLint _channels;
	GLuint _id;

	void _free();

public:
	Texture(const GLchar* path, bool isFlipY = true);
	~Texture();

	void Use() { glBindTexture(GL_TEXTURE_2D, _id); }
};

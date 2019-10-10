#pragma once
#include <glad/glad.h>

class Texture
{
public:
	GLint GetWidth() const
	{
		return mWidth;
	}

	GLint GetHeight() const
	{
		return mHeight;
	}

	unsigned char* GetData() const
	{
		return mData;
	}

	GLint GetChannels() const
	{
		return mChannels;
	}

	GLuint GetID() const
	{
		return mId;
	}

private:
	GLint mWidth;
	GLint mHeight;
	unsigned char* mData;
	GLint mChannels;
	GLuint mId;

	void Free();

public:
	Texture(const GLchar* path, bool isFlipY = true);
	~Texture();

	void Use() { glBindTexture(GL_TEXTURE_2D, mId); }
};

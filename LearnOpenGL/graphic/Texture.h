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

	GLint mWrapStyle;

	void Free();
	void CreateTextureInner(const GLchar* path, bool isFlipY);

public:
	Texture(const GLchar* path, GLint wrapStyle, bool isFlipY = true);
	Texture(const GLchar* path, bool isFlipY = true);
	~Texture();

	void SetWrapStyle(GLint wrapStyle);

	void Use()
	{
		glBindTexture(GL_TEXTURE_2D, mId);
	}
};

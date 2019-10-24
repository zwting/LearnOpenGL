#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include "../commons/Debug.h"

void Texture::Free()
{
	if (mData != nullptr)
	{
		stbi_image_free(mData);
		mData = nullptr;
	}
}

void Texture::CreateTextureInner(const GLchar* path, bool isFlipY)
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapStyle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapStyle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(isFlipY);
	this->mData = stbi_load(path, &mWidth, &mHeight, &mChannels, 0);
	if (mData)
	{
		GLenum format = GL_RGB;
		if (mChannels == 1) format = GL_RED;
		else if (mChannels == 3) format = GL_RGB;
		else if (mChannels == 4) format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	Free();
}

Texture::Texture(const GLchar* path, GLint WrapStyle, bool isFlipY)
{
	mWrapStyle = WrapStyle;
	CreateTextureInner(path, isFlipY);
}

Texture::Texture(const GLchar* path, bool isFlipY)
{
	mWrapStyle = GL_REPEAT;
	CreateTextureInner(path, isFlipY);
}

Texture::~Texture()
{
	Free();
}

void Texture::SetWrapStyle(GLint wrapStyle)
{
	mWrapStyle = wrapStyle;
	if(!glIsTexture(mId))
	{
		Debug::Log("%d is not a texture object", mId);
		return;
	}

	glBindTexture(GL_TEXTURE_2D,mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapStyle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapStyle);
	glBindTexture(GL_TEXTURE_2D, 0);
}

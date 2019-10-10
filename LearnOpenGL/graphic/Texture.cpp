#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

void Texture::Free()
{
	if (mData != nullptr)
	{
		stbi_image_free(mData);
		mData = nullptr;
	}
}

Texture::Texture(const GLchar* path, bool isFlipY)
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(isFlipY);
	this->mData = stbi_load(path, &mWidth, &mHeight, &mChannels, 0);
	if (mData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	Free();
}

Texture::~Texture()
{
	Free();
}

#pragma once
#include <iostream>
#include "MathType.h"
#include <vector>
#include "../graphic/Texture.h"
#include "../graphic/Shader.h"


struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 Texcoord;
};

struct MeshTexture
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Normal,
		Height,
	};

	Texture* pTexture;
	TextureType Type;
	std::string Path;

	MeshTexture(std::string texturePath, TextureType textureType = TextureType::Diffuse)
		: Type(textureType),
		  Path(texturePath)
	{
		pTexture = new Texture(Path.c_str());
	}
};


class Mesh
{
public:
	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;
	std::vector<MeshTexture> mTextures;

	Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<MeshTexture> textures);
	void Render(const Shader* shader);
	void AddTexture(MeshTexture texture);

private:
	unsigned int mVAO, mVBO, mEBO;
	void SetupMesh();
};

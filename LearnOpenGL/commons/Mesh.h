#pragma once
#include <iostream>
#include "MathType.h"
#include <vector>
#include "../graphic/Texture.h"
#include "../graphic/Shader.h"


struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texcoord;
};

struct MeshTexture
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Normal,
	};

	Texture* texture;
	TextureType type;
	std::string path;

	MeshTexture(std::string texturePath, TextureType textureType = TextureType::Diffuse)
		: type(textureType),
		  path(texturePath)
	{
		texture = new Texture(path.c_str());
	}
};


class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture> textures;

	Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<MeshTexture> textures);
	void Render(const Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void SetupMesh();
};

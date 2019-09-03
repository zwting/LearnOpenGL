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


class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

	Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture*> textures);
	void Render(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void SetupMesh();
};

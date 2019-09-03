#include "PrimitiveModel.h"

Node* PrimitiveModel::CreatePrimitive(const PrimitiveType type)
{
	Node* ret = nullptr;
	switch (type)
	{
	case PrimitiveType::Cube:
		ret = new Node(vec3_zero, qua_identity);
		
		break;
	}

	return ret;
}

Mesh* PrimitiveModel::getCubeMesh()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture*> textures;

	

	
	return new Mesh(vertices, indices, textures);
}

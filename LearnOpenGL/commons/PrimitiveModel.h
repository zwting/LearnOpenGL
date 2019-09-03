#pragma once
#include "Node.h"

class PrimitiveModel
{
public:
	enum class PrimitiveType
	{
		Cube,
	};
public:
	static Node* CreatePrimitive(const PrimitiveType type);

private:
	static Mesh* getCubeMesh();
};

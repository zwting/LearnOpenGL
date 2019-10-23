#pragma once
#include "Node.h"
#include <iostream>
#include <map>

class PrimitiveModel
{
public:
	enum class PrimitiveType
	{
		Cube, //立方体
		Quad, //面片
	};
public:
	static Node* CreatePrimitive(const PrimitiveType type);
	static std::map<PrimitiveType, Model*> cachedModel;

private:
	static Model* GetModel(PrimitiveType type);
};

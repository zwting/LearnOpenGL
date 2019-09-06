#pragma once
#include "Node.h"
#include <iostream>
#include <map>

class PrimitiveModel
{
public:
	enum class PrimitiveType
	{
		Cube,
	};
public:
	static Node* CreatePrimitive(const PrimitiveType type);
	static std::map<PrimitiveType, Model*> cachedModel;

private:
	static Model* GetModel(PrimitiveType type);
};

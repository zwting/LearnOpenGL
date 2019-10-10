#include "PrimitiveModel.h"

std::map<PrimitiveModel::PrimitiveType, Model*> PrimitiveModel::cachedModel;

Node* PrimitiveModel::CreatePrimitive(const PrimitiveType type)
{
	Node* ret = nullptr;
	switch (type)
	{
	case PrimitiveType::Cube:
		ret = new Node(vec3_zero, qua_identity);
		ret->SetModel(GetModel(type));
		break;
	}

	return ret;
}

Model* PrimitiveModel::GetModel(PrimitiveType type)
{
	if (cachedModel[type]) return cachedModel[type];

	switch (type)
	{
	case PrimitiveType::Cube:
		static Model* model = new Model("resources/model/cube.obj");
		cachedModel[type] = model;
		break;
	default:
		return cachedModel[PrimitiveType::Cube];
	}

	return cachedModel[type];
}

#pragma once
#include <vector>
#include "Mesh.h"
#include "Model.h"

class Node
{
private:
	quaternion rotation;
	vec3 position;
	vec3 forward{};
	vec3 right{};
	vec3 up{};

	bool isTransformDirty{};

	mat4x4 modelMatrix{};

	Model* model;
public:
	Model* getModel() const
	{
		return model;
	}

	void setModel(Model* model)
	{
		this->model = model;
	}

	const mat4x4& getModelMatrix()
	{
		checkTransformIsDirty();
		return this->modelMatrix;
	}

	quaternion getRotation() const
	{
		return rotation;
	}

	vec3 getPosition() const
	{
		return position;
	}

	void setRotation(quaternion rotation)
	{
		isTransformDirty = true;
		this->rotation = rotation;
	}

	void setPosition(vec3 position)
	{
		isTransformDirty = true;
		this->position = position;
	}

	vec3 getForward()
	{
		checkTransformIsDirty();
		return forward;
	}

	vec3 getRight()
	{
		checkTransformIsDirty();
		return right;
	}

	vec3 getUp()
	{
		checkTransformIsDirty();
		return up;
	}

private:
	//检查transform是否需要更新
	void checkTransformIsDirty()
	{
		if(isTransformDirty)
		{
			calcModelMatrix();
		}
	}

public:
	Node(vec3 pos, quaternion rot)
		:
		rotation(rot),
		position(pos)
	{
		modelMatrix = mat_identity;
		isTransformDirty = true;

		calcModelMatrix();
	}

	~Node();

	void calcModelMatrix();

	void Render(Shader* shader)
	{
		if(model)
		{
			model->Render(shader);
		}
	};
};

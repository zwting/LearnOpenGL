#pragma once
#include <vector>
#include "Mesh.h"
#include "Model.h"

class Node
{
private:
	quaternion mRotation;
	vec3 mPosition;
	vec3 mScale;


private:
	vec3 mForward{};
	vec3 mRight{};
	vec3 mUp{};

	bool mIsTransformDirty{};

	mat4x4 mModelMatrix{};

	Model* mpModel;
public:
	vec3 GetScale() const
	{
		return mScale;
	}

	void SetScale(const vec3& scale)
	{
		mIsTransformDirty = true;
		this->mScale = scale;
	}

	Model* GetModel() const
	{
		return mpModel;
	}

	void SetModel(Model* model)
	{
		this->mpModel = model;
	}

	const mat4x4& GetModelMatrix()
	{
		CheckTransformIsDirty();
		return this->mModelMatrix;
	}

	quaternion GetRotation() const
	{
		return mRotation;
	}

	vec3 GetPosition() const
	{
		return mPosition;
	}

	void SetRotation(quaternion rot)
	{
		mIsTransformDirty = true;
		this->mRotation = glm::normalize(rot);
	}

	void SetPosition(const vec3& position)
	{
		mIsTransformDirty = true;
		this->mPosition = position;
	}

	void SetPosition(float x, float y, float z)
	{
		mIsTransformDirty = true;
		this->mPosition.x = x;
		this->mPosition.y = y;
		this->mPosition.z = z;
	}

	vec3 GetForward()
	{
		CheckTransformIsDirty();
		return mForward;
	}

	void SetForward(const vec3& forward)
	{
		mIsTransformDirty = true;
		this->mForward = forward;
	}

	vec3 GetRight()
	{
		CheckTransformIsDirty();
		return mRight;
	}
	void SetRight(const vec3& right)
	{
		mIsTransformDirty = true;
		this->mRight = right;
	}

	vec3 GetUp()
	{
		CheckTransformIsDirty();
		return mUp;
	}
	void SetUp(const vec3& up)
	{
		mIsTransformDirty = true;
		this->mUp = up;
	}

private:
	//检查transform是否需要更新
	void CheckTransformIsDirty()
	{
		if(mIsTransformDirty)
		{
			CalcModelMatrix();
		}
	}

public:
	Node(vec3 pos, quaternion rot)
		:
		mRotation(rot),
		mPosition(pos)
	{
		mModelMatrix = mat_identity;
		mIsTransformDirty = true;
		mScale = vec3_one;

		CalcModelMatrix();
	}

	~Node();

	void CalcModelMatrix();

	void Rotate(const quaternion& q);

	void LookAt(const vec3& target, const vec3& up = vec3_up);

	void Render(Shader* shader)
	{
		if(mpModel)
		{
			shader->SetMat4vf("model",value_ptr(GetModelMatrix()));
			mpModel->Render(shader);
		}
	}
};

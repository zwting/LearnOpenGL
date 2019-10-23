#pragma once
#include <vector>
#include "Model.h"
#include "CommonUtils.h"
#include <functional>

class Node
{
public:
private:
	quaternion mRotation;
	vec3 mPosition;
	vec3 mScale;
	std::function<void()> mDirtyCallback;

private:
	bool mIsTransformDirty{};

	mat4x4 mModelMatrix{};

	Model* mpModel;
public:
	void SetDirtyCallback(std::function<void()> callback)
	{
		mDirtyCallback = callback;
	}

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
		if(mIsTransformDirty)
		{
			CalcModelMatrix();
		}
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
		CheckIsDirty();
	}

	void SetPosition(const vec3& position)
	{
		mIsTransformDirty = true;
		this->mPosition = position;
		CheckIsDirty();
	}

	void SetPosition(float x, float y, float z)
	{
		mIsTransformDirty = true;
		this->mPosition.x = x;
		this->mPosition.y = y;
		this->mPosition.z = z;
		CheckIsDirty();
	}

	vec3 GetForward() const
	{
		return mRotation * VEC3_FORWARD;
	}

	void SetForward(const vec3& forward)
	{
		mIsTransformDirty = true;
		mRotation = CommonUtils::FromDirectionTo(VEC3_FORWARD , forward);
		CheckIsDirty();
	}

	vec3 GetRight() const
	{
		return mRotation * VEC3_RIGHT;
	}
	void SetRight(const vec3& right)
	{
		mIsTransformDirty = true;
		mRotation = CommonUtils::FromDirectionTo(VEC3_RIGHT, right);
		CheckIsDirty();
	}

	vec3 GetUp() const
	{
		return mRotation * VEC3_UP;
	}
	void SetUp(const vec3& up)
	{
		mIsTransformDirty = true;
		mRotation = CommonUtils::FromDirectionTo(VEC3_UP, up);
		CheckIsDirty();
	}

private:
	//检查transform是否需要更新
	void CheckIsDirty() const;

public:
	Node(vec3 pos, quaternion rot)
		:
		mRotation(rot),
		mPosition(pos)
	{
		mModelMatrix = MAT_IDENTITY;
		mIsTransformDirty = true;
		mDirtyCallback = nullptr;
		mScale = VEC3_ONE;

		CalcModelMatrix();
		CheckIsDirty();
	}

	~Node();


	void CalcModelMatrix();

	void Rotate(const quaternion& q);

	void LookAt(const vec3& target, const vec3& up = VEC3_UP);

	void Render(const Shader* shader)
	{
		if(mpModel)
		{
			shader->SetMat4vf("model",VALUE_PTR(GetModelMatrix()));
			mpModel->Render(shader);
		}
	}
};

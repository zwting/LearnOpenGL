#pragma once
#include "MathType.h"
#include "Node.h"

class Camera
{
private:
	Node* mNode;

	vec3 mUp;

	float mFov;
	float mNear;
	float mFar;
	float mAspect;

	bool mIsViewDirty;
	bool mIsProjDirty;

	mat4x4 mViewMatrix{};
	mat4x4 mProjMatrix{};

public:
	Node* GetNode() const
	{
		return mNode;
	}

	vec3 GetPosition() const
	{
		return mNode->GetPosition();
	}

	void SetPosition(vec3 vec)
	{
		mIsViewDirty = true;
		mNode->SetPosition(vec);
	}

	vec3 GetUp() const
	{
		return mNode->GetUp();
	}

	vec3 GetRight() const
	{
		return mNode->GetRight();
	}

	vec3 GetForward()const
	{
		return -mNode->GetForward();
	}


public:
	Camera(vec3 pos, vec3 target, float fov, float aspect, float near, float far, vec3 worldUp = vec3_up);
	const mat4x4& GetViewMatrix();
	const mat4x4& GetProjMatrix() const;
	void LookAt(const vec3& target, const vec3& worldUp = vec3_up);
	void UpdateViewMatrix();
	void Rotate(const quaternion& q);
};

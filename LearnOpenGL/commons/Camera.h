#pragma once
#include "MathType.h"

class Camera
{
private:
	vec3 mPosition;
	vec3 mForward;
	vec3 mUp;
	vec3 mWorldUp;
	vec3 mRight;

	float mFov;
	float mNear;
	float mFar;

	mat4x4 mViewMatrix = mat_identity;
	mat4x4 mProjMatrix = mat_identity;

public:
	vec3 GetPosition() const
	{
		return mPosition;
	}

	void SetPosition(const vec3& vec3)
	{
		mPosition = vec3;
	}

	vec3 GetForward() const
	{
		return mForward;
	}

	vec3 GetUp() const
	{
		return mUp;
	}

	void SetUp(const vec3& vec3)
	{
		mUp = vec3;
	}

	vec3 GetRight() const
	{
		return mRight;
	}


public:
	Camera(vec3& pos, vec3& forward, float fov, float near, float far, vec3 worldUp = vec3_up);
	const mat4x4& GetViewMatrix();
	const mat4x4& GetProjMatrix();
	void LookAt(const vec3& target, const vec3& worldUp = vec3_up);

};

#pragma once
#include "MathType.h"

class Camera
{
private:
	vec3 position{};
	vec3 forward{};
	vec3 up{};
	vec3 worldUp{};
	vec3 right{};

	float fov;
	float near;
	float far;
	float aspect;

	bool isDirty;

	mat4x4 viewMatrix{};
	mat4x4 projMatrix{};

public:
	vec3 getPosition() const
	{
		return position;
	}

	void setPosition(vec3 vec)
	{
		isDirty = true;
		position = vec;
	}

	vec3 getForward() const
	{
		return forward;
	}

	vec3 getUp() const
	{
		return up;
	}

	void setUp(vec3 vec)
	{
		isDirty = true;
		up = vec;
	}

	vec3 getRight() const
	{
		return right;
	}


public:
	Camera(vec3 pos, vec3 forward, float fov, float aspect, float near, float far, vec3 worldUp = vec3_up);
	const mat4x4& getViewMatrix();
	const mat4x4& getProjMatrix();
	void lookAt(const vec3& target, const vec3& worldUp = vec3_up);
	void calcViewMatrix();
};

#pragma once
#include "MathType.h"
#include "Node.h"

class Camera
{
private:
	Node* node;

	vec3 forward;
	vec3 up;

	float fov;
	float near;
	float far;
	float aspect;

	bool isDirty;

	mat4x4 viewMatrix{};
	mat4x4 projMatrix{};

public:
	Node* getNode() const
	{
		return node;
	}

	vec3 getPosition() const
	{
		return node->getPosition();
	}

	void setPosition(vec3 vec)
	{
		isDirty = true;
		node->setPosition(vec);
	}

	vec3 getForward() const
	{
		return forward;
	}

	vec3 getUp() const
	{
		return node->getUp();
	}

	vec3 getRight() const
	{
		return node->getRight();
	}


public:
	Camera(vec3 pos, vec3 forward, float fov, float aspect, float near, float far, vec3 worldUp = vec3_up);
	const mat4x4& getViewMatrix();
	const mat4x4& getProjMatrix() const;
	void lookAt(const vec3& target, const vec3& worldUp = vec3_up);
	void calcViewMatrix();
	void rotate(const quaternion& q);
};

#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(vec3 pos, vec3 forward, float fov, float aspect, float near, float far, vec3 up)
{
	this->position = pos;
	this->forward = forward;
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->worldUp = up;
	this->aspect = aspect;

	this->isDirty = true;

	viewMatrix = mat_identity;

	projMatrix = glm::perspective(
		glm::radians(fov),
		aspect,
		near,
		far
	);
}

const mat4x4& Camera::getViewMatrix()
{
	if (isDirty)
	{
		calcViewMatrix();
	}
	return viewMatrix;
}

const mat4x4& Camera::getProjMatrix()
{
	return projMatrix;
}

void Camera::lookAt(const vec3& target, const vec3& worldUp)
{
	forward = glm::normalize(target - position);
	right = glm::cross(forward, glm::normalize(worldUp));
	up = glm::cross(right, forward);

	isDirty = true;
}

void Camera::calcViewMatrix()
{
	viewMatrix[0][0] = right.x;
	viewMatrix[1][0] = right.y;
	viewMatrix[2][0] = right.z;

	viewMatrix[0][1] = up.x;
	viewMatrix[1][1] = up.y;
	viewMatrix[2][1] = up.z;

	viewMatrix[0][2] = -forward.x;
	viewMatrix[1][2] = -forward.y;
	viewMatrix[2][2] = -forward.z;

	viewMatrix[3][0] = -glm::dot(right, position);
	viewMatrix[3][1] = -glm::dot(up, position);
	viewMatrix[3][2] = glm::dot(forward, position);
}

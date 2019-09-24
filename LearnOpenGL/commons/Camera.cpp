#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(vec3 pos, vec3 target, float fov, float aspect, float near, float far, vec3 up)
{
	this->node = new Node(pos, qua_identity);
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->up = up;
	this->aspect = aspect;

	this->isViewDirty = true;

	viewMatrix = mat_identity;

	lookAt(target, up);

	projMatrix = glm::perspective(
		glm::radians(fov),
		aspect,
		near,
		far
	);
}

const mat4x4& Camera::getViewMatrix()
{
	if (isViewDirty)
	{
		updateViewMatrix();
	}
	return viewMatrix;
}

const mat4x4& Camera::getProjMatrix() const
{
	return projMatrix;
}

void Camera::lookAt(const vec3& target, const vec3& worldUp)
{
	this->up = worldUp;
	const vec3 pos = node->getPosition();
	// viewMatrix = glm::lookAt(target, pos, worldUp);
	const vec3 forward = glm::normalize(pos - target);
	const vec3 right = glm::cross(this->up, forward);
	const vec3 up = glm::cross(forward, right);

	this->node->setForward(forward);
	this->node->setRight(right);
	this->node->setUp(up);

	isViewDirty = true;
}

//由相机的view矩阵来驱动更新node 的 model矩阵
void Camera::updateViewMatrix()
{
	const vec3 pos = node->getPosition();

	const vec3 right = node->getRight();
	const vec3 up = node->getUp();
	const vec3 forward = node->getForward();

	viewMatrix[0][0] = right.x;
	viewMatrix[1][0] = right.y;
	viewMatrix[2][0] = right.z;

	viewMatrix[0][1] = up.x;
	viewMatrix[1][1] = up.y;
	viewMatrix[2][1] = up.z;

	viewMatrix[0][2] = forward.x;
	viewMatrix[1][2] = forward.y;
	viewMatrix[2][2] = forward.z;

	viewMatrix[3][0] = -glm::dot(right, pos);
	viewMatrix[3][1] = -glm::dot(up, pos);
	viewMatrix[3][2] = -glm::dot(forward, pos);

	isViewDirty = false;
}

void Camera::rotate(const quaternion& q)
{
	// forward = glm::normalize(q * forward);
	// isViewDirty = true;
}

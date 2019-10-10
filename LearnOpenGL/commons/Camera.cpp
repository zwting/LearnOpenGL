#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(vec3 pos, vec3 target, float fov, float aspect, float near, float far, vec3 up)
{
	this->mNode = new Node(pos, qua_identity);
	this->mFov = fov;
	this->mNear = near;
	this->mFar = far;
	this->mUp = up;
	this->mAspect = aspect;

	this->mIsViewDirty = true;

	mViewMatrix = mat_identity;

	LookAt(target, up);

	mProjMatrix = glm::perspective(
		glm::radians(fov),
		aspect,
		near,
		far
	);
}

const mat4x4& Camera::GetViewMatrix()
{
	if (mIsViewDirty)
	{
		UpdateViewMatrix();
	}
	return mViewMatrix;
}

const mat4x4& Camera::GetProjMatrix() const
{
	return mProjMatrix;
}

void Camera::LookAt(const vec3& target, const vec3& worldUp)
{
	this->mUp = worldUp;
	const vec3 pos = mNode->GetPosition();
	// viewMatrix = glm::lookAt(target, pos, worldUp);
	const vec3 forward = glm::normalize(pos - target);
	const vec3 right = glm::cross(this->mUp, forward);
	const vec3 up = glm::cross(forward, right);

	this->mNode->SetForward(forward);
	this->mNode->SetRight(right);
	this->mNode->SetUp(up);

	mIsViewDirty = true;
}

//由相机的view矩阵来驱动更新node 的 model矩阵
void Camera::UpdateViewMatrix()
{
	const vec3 pos = mNode->GetPosition();

	const vec3 right = mNode->GetRight();
	const vec3 up = mNode->GetUp();
	const vec3 forward = mNode->GetForward();

	mViewMatrix[0][0] = right.x;
	mViewMatrix[1][0] = right.y;
	mViewMatrix[2][0] = right.z;

	mViewMatrix[0][1] = up.x;
	mViewMatrix[1][1] = up.y;
	mViewMatrix[2][1] = up.z;

	mViewMatrix[0][2] = forward.x;
	mViewMatrix[1][2] = forward.y;
	mViewMatrix[2][2] = forward.z;

	mViewMatrix[3][0] = -glm::dot(right, pos);
	mViewMatrix[3][1] = -glm::dot(up, pos);
	mViewMatrix[3][2] = -glm::dot(forward, pos);

	mIsViewDirty = false;
}

void Camera::Rotate(const quaternion& q)
{
	mNode->SetRotation(q);
	mIsViewDirty = true;
}

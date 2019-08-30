#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(vec3& pos, vec3& forward, float fov, float near, float far, vec3 up)
{
	mPosition = pos;
	mForward = forward;
	mFov = fov;
	mNear = near;
	mFar = far;
	mWorldUp = up;
}

const mat4x4& Camera::GetViewMatrix()
{
	mViewMatrix[0][0] = -mRight.x;
	mViewMatrix[1][0] = -mRight.y;
	mViewMatrix[2][0] = -mRight.z;

	mViewMatrix[0][0] = mUp.x;
	mViewMatrix[1][0] = mUp.y;
	mViewMatrix[2][0] = mUp.z;

	mViewMatrix[0][0] = mForward.x;
	mViewMatrix[1][0] = mForward.y;
	mViewMatrix[2][0] = mForward.z;

	mViewMatrix[3][0] = glm::dot(mRight, mPosition);
	mViewMatrix[3][1] = glm::dot(mUp, mPosition);
	mViewMatrix[3][2] = glm::dot(mForward, mPosition);

	return mViewMatrix;
}

const mat4x4& Camera::GetProjMatrix()
{
	return mProjMatrix;
}

void Camera::LookAt(const vec3& target, const vec3& worldUp)
{
	mForward = glm::normalize(target - mPosition);
	mRight = glm::cross(mForward, worldUp);
	mUp = glm::cross(mRight, mForward);
}
